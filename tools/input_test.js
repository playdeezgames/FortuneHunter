// Tests the gamepad mapping in odin/platform/web/page/input.js (the touch part needs a browser). Run by tools/test.sh.
const fs = require("fs");
const vm = require("vm");
const assert = require("assert");
const source = fs.readFileSync(__dirname + "/../odin/platform/web/page/input.js", "utf8");
const context = { navigator: {}, console };
vm.createContext(context);
vm.runInContext(source + "\nthis.createGamepads = createGamepads; this.GAMEPAD_BUTTONS = GAMEPAD_BUTTONS;", context);

const sent = [];
let presses = 0;
const pads = context.createGamepads((name) => sent.push(name), () => presses++);
const pad = (index, mapping = "standard") => ({ index, mapping, connected: true, buttons: Array.from({ length: 17 }, () => ({ pressed: false })) });
const press = (p, ...i) => i.forEach((n) => (p.buttons[n].pressed = true));
const release = (p) => p.buttons.forEach((b) => (b.pressed = false));
const frame = (...ps) => { pads.getPads = () => ps; pads.poll(); };

const a = pad(0);
frame(a); assert.deepStrictEqual(sent, []);
press(a, 0); frame(a); assert.deepStrictEqual(sent, ["green"]);
frame(a); frame(a); assert.deepStrictEqual(sent, ["green"], "a held button is one command");
release(a); frame(a); press(a, 0); frame(a); assert.deepStrictEqual(sent.slice(1), ["green"]);
release(a); frame(a); sent.length = 0;

// every mapped button, one per frame
const expected = { 0: "green", 1: "red", 2: "blue", 3: "yellow", 4: "previous", 5: "next", 8: "back", 9: "start", 12: "up", 13: "down", 14: "left", 15: "right" };
for (const [i, name] of Object.entries(expected)) { press(a, Number(i)); frame(a); release(a); frame(a); assert.strictEqual(sent.pop(), name, "button " + i); }
assert.strictEqual(JSON.stringify(context.GAMEPAD_BUTTONS), JSON.stringify(expected), "no other buttons are mapped");

// unmapped buttons (sticks, triggers, guide) do nothing; two pads at once; non-standard and disconnected pads are ignored
press(a, 6, 7, 10, 11, 16); frame(a); assert.deepStrictEqual(sent, []); release(a); frame(a);
const b = pad(1); press(a, 12); press(b, 13); frame(a, b); assert.deepStrictEqual(sent.splice(0), ["up", "down"]);
const odd = pad(2, ""); press(odd, 0); frame(odd); assert.deepStrictEqual(sent, []);
const gone = pad(3); gone.connected = false; press(gone, 0); frame(gone); assert.deepStrictEqual(sent, []);
frame(null, undefined); // empty slots in navigator.getGamepads()
assert.ok(presses > 10, "every command reports a press so the page can unlock audio");
console.log("input.js gamepad tests passed");
