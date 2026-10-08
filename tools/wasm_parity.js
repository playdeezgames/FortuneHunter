// Runs the built web platform (build/web/platform.wasm) under node through the same scripted game as
// odin/tests/parity_test.odin runs natively, and writes the same digest. tools/test.sh requires the two to be equal: that
// proves the wasm build (32-bit int, its own allocator) plays exactly like the native one.
// Usage: ODIN_JS=<odin.js> node tools/wasm_parity.js build/web build/parity_wasm.txt
const fs = require("fs"), vm = require("vm");
global.window = global; global.self = global;
global.requestAnimationFrame = (f) => setTimeout(() => f(performance.now()), 0);
vm.runInThisContext(fs.readFileSync(process.env.ODIN_JS, "utf8"));
vm.runInThisContext(fs.readFileSync(process.argv[2] + "/storage.js", "utf8"));
const store = new Map();
global.localStorage = { getItem: (k) => (store.has(k) ? store.get(k) : null), setItem: (k, v) => store.set(k, String(v)), removeItem: (k) => store.delete(k) };
global.fetch = async (p) => ({ ok: true, arrayBuffer: async () => fs.readFileSync(p) });

const STEPS = +(process.env.PARITY_STEPS || 6000);
const IMAGES = "build/parity_images";
let lcg = 12345;
const next = () => { lcg = (Math.imul(lcg, 1664525) + 1013904223) >>> 0; return lcg; };
const fnv = (h, word) => (Math.imul(h ^ word, 16777619) >>> 0);
const command = (step) => { // same weights as parity_command in parity_test.odin
  const roll = (next() >>> 16) % 100;
  if (step < Math.floor(STEPS * 2 / 3)) return roll < 85 ? 1 + (roll % 4) : 5; // arrows and green only
  if (roll < 55) return 1 + (roll % 4);
  if (roll < 70) return 5;   // green
  if (roll < 78) return 12;  // start
  if (roll < 86) return 11;  // back
  if (roll < 90) return 9;   // next
  if (roll < 94) return 10;  // previous
  if (roll < 97) return 6;   // red
  if (roll < 99) return 8;   // blue
  return 7;                  // yellow
};

(async () => {
  const mem = new odin.WasmMemoryInterface();
  let half = 0;
  const platform = { js_entropy_u32() { half ^= 1; return half ? 0 : 7; }, js_log() {} }; // entropy is 7, as in the native test
  await odin.runWasm(process.argv[2] + "/platform.wasm", null, { ...storageImports(mem), platform }, mem);
  const ex = mem.exports;

  // the images the native test dumped (name: id_WxH.rgba)
  const files = fs.readdirSync(IMAGES).filter((f) => f.endsWith(".rgba"));
  assert(files.length === ex.platform_image_count(), "expected " + ex.platform_image_count() + " dumped images, found " + files.length);
  for (const f of files) {
    const [, id, w, h] = /^(\d+)_(\d+)x(\d+)\.rgba$/.exec(f);
    const data = fs.readFileSync(IMAGES + "/" + f);
    const ptr = ex.platform_alloc(data.length);
    new Uint8Array(mem.memory.buffer, ptr, data.length).set(data);
    assert(ex.platform_set_image(+id, +w, +h, ptr), "core rejected image " + id);
  }
  function assert(ok, message) { if (!ok) throw new Error(message); }

  let frames = 2166136261, sounds = 2166136261, clipboard = 2166136261;
  let now = 1790000000000;
  const W = 640, H = 480;
  for (let step = 0; step < STEPS; step++) {
    const rolled = command(step); // always rolled, as in the Odin test
    ex.platform_command(step === 0 ? 2 : step === 1 ? 5 : rolled); // down, green: hard difficulty first
    now += 16;
    ex.platform_frame(0.016, now);
    const words = new Uint32Array(mem.memory.buffer, ex.platform_frame_ptr(), W * H);
    if (step % 5 === 0) for (let i = 0; i < words.length; i++) frames = fnv(frames, words[i]);
    else for (let i = 0; i < 64; i++) frames = fnv(frames, words[(i * 4813) % words.length]);
    const n = ex.platform_sounds_len();
    if (n > 0) for (const id of new Uint8Array(mem.memory.buffer, ex.platform_sounds_ptr(), n)) sounds = fnv(sounds, id);
    sounds = fnv(sounds, n);
    const clipLen = ex.platform_clipboard_len();
    if (clipLen > 0) for (const b of new Uint8Array(mem.memory.buffer, ex.platform_clipboard_ptr(), clipLen)) clipboard = fnv(clipboard, b);
    frames = fnv(frames, (ex.platform_sfx_volume() + (ex.platform_quit() ? 1 << 16 : 0)) >>> 0);
  }
  let saved = 2166136261;
  for (const key of ["fh:options", "fh:statistics"]) for (const b of Buffer.from(store.get(key) || "")) saved = fnv(saved, b);
  const stats = JSON.parse(store.get("fh:statistics") || '{"gamesPlayed":0}');
  fs.writeFileSync(process.argv[3], `frames=${frames} sounds=${sounds} clipboard=${clipboard} saved=${saved} games=${stats.gamesPlayed}\n`);
  console.log("wasm parity digest written");
})().catch((e) => { console.error("FAILED:", e); process.exit(1); });
