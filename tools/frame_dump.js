// Plays a list of commands through the built wasm under node and writes the last 640x480 frame as raw RGBA.
// Usage: ODIN_JS=<odin.js> node tools/frame_dump.js build/web SEED out.rgba command,command,...   (needs build/parity_images from a test run)
const fs = require("fs"), vm = require("vm");
global.window = global; global.self = global;
global.requestAnimationFrame = (f) => setTimeout(() => f(performance.now()), 0);
vm.runInThisContext(fs.readFileSync(process.env.ODIN_JS, "utf8"));
vm.runInThisContext(fs.readFileSync(process.argv[2] + "/storage.js", "utf8"));
const store = new Map();
global.localStorage = { getItem: (k) => (store.has(k) ? store.get(k) : null), setItem: (k, v) => store.set(k, String(v)), removeItem: (k) => store.delete(k) };
global.fetch = async (p) => ({ ok: true, arrayBuffer: async () => fs.readFileSync(p) });
const COMMAND = { up: 1, down: 2, left: 3, right: 4, green: 5, red: 6, yellow: 7, blue: 8, next: 9, previous: 10, back: 11, start: 12 };
(async () => {
  const mem = new odin.WasmMemoryInterface();
  let half = 0;
  const seed = +process.argv[3];
  const platform = { js_entropy_u32() { half ^= 1; return half ? 0 : seed; }, js_log() {} };
  await odin.runWasm(process.argv[2] + "/platform.wasm", null, { ...storageImports(mem), platform }, mem);
  const ex = mem.exports;
  for (const f of fs.readdirSync("build/parity_images")) {
    const [, id, w, h] = /^(\d+)_(\d+)x(\d+)\.rgba$/.exec(f);
    const data = fs.readFileSync("build/parity_images/" + f);
    const ptr = ex.platform_alloc(data.length);
    new Uint8Array(mem.memory.buffer, ptr, data.length).set(data);
    if (!ex.platform_set_image(+id, +w, +h, ptr)) throw new Error("image " + id);
  }
  ex.platform_frame(0.016, Date.now());
  for (const name of (process.argv[5] || "").split(",").filter(Boolean)) {
    ex.platform_command(COMMAND[name]);
    ex.platform_frame(0.016, Date.now());
  }
  fs.writeFileSync(process.argv[4], Buffer.from(new Uint8Array(mem.memory.buffer, ex.platform_frame_ptr(), 640 * 480 * 4)));
})().catch((e) => { console.error(e); process.exit(1); });
