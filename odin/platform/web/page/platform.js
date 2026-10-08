// Browser side of the platform interface: decode the images for the core, draw its 640x480 RGBA frame,
// turn keys (here), gamepad buttons and touches (input.js) into commands.
(async function () {
	const FRAME_W = 640, FRAME_H = 480;
	// Same order as the Command enum in odin/game/api.odin (0 is None).
	const COMMAND = { up: 1, down: 2, left: 3, right: 4, green: 5, red: 6, yellow: 7, blue: 8, next: 9, previous: 10, back: 11, start: 12 };
	const params = new URLSearchParams(location.search);
	const debugLog = params.has("log"); // ?log=1 prints every input sent to the game
	const logInput = (...a) => { if (debugLog) console.log("[input]", ...a); };
	// ?keys=start,down,green,... plays those commands, one per frame, once the game is up (QA and screenshots)
	const scriptedKeys = (params.get("keys") || "").split(",").filter((k) => k in COMMAND);
	const seedParam = params.get("seed"); // ?seed=N fixes the random numbers (bug reports, tests)
	const fixedSeed = seedParam !== null && /^\d{1,9}$/.test(seedParam) ? Number(seedParam) : null;
	let fixedSeedHalf = 0;

	const mem = new odin.WasmMemoryInterface();
	const platformImports = {
		// with a fixed seed the high word is 0 and the low word is N
		js_entropy_u32() {
			if (fixedSeed !== null) { fixedSeedHalf ^= 1; return fixedSeedHalf ? 0 : fixedSeed; }
			return crypto.getRandomValues(new Uint32Array(1))[0] | 0;
		},
		js_log(p, n) { console.log(mem.loadString(p, n)); },
	};
	await odin.runWasm("platform.wasm", null, { ...storageImports(mem), platform: platformImports }, mem);
	const exports = mem.exports;

	// ---- images: decode every file the core lists and hand over RGBA pixels ------------------------------
	async function loadImages() {
		const scratch = document.createElement("canvas");
		const sctx = scratch.getContext("2d", { willReadFrequently: true });
		for (let id = 0; id < exports.platform_image_count(); id++) {
			const path = mem.loadString(exports.platform_image_path_ptr(id), exports.platform_image_path_len(id));
			const response = await fetch(path);
			if (!response.ok) throw new Error("cannot load " + path);
			const bitmap = await createImageBitmap(await response.blob(), { premultiplyAlpha: "none", colorSpaceConversion: "none" });
			scratch.width = bitmap.width; scratch.height = bitmap.height;
			sctx.clearRect(0, 0, bitmap.width, bitmap.height);
			sctx.drawImage(bitmap, 0, 0);
			const data = sctx.getImageData(0, 0, bitmap.width, bitmap.height).data;
			const ptr = exports.platform_alloc(data.length);
			if (!ptr) throw new Error("out of memory for " + path);
			new Uint8Array(mem.memory.buffer, ptr, data.length).set(data); // read the buffer after the alloc: memory may have grown
			if (!exports.platform_set_image(id, bitmap.width, bitmap.height, ptr)) throw new Error("core rejected " + path);
		}
	}
	try { await loadImages(); } catch (e) { console.error(e); }

	// ---- audio: decode the sound files the core lists; nothing plays before the first key press -------------------
	const audio = createAudio(exports, mem);
	audio.load().catch((e) => console.error(e));
	const unlockAudio = () => audio.unlock();
	addEventListener("pointerdown", unlockAudio);

	// ---- layout: the largest whole multiple of the frame that fits, else a smooth fit; centred on black ----------
	const canvas = document.getElementById("screen"), ctx = canvas.getContext("2d");
	let laidOutFor = "";
	function layout() {
		const w = innerWidth, h = innerHeight;
		laidOutFor = w + "x" + h;
		if (w === 0 || h === 0) return;
		let scale = Math.min(w / FRAME_W, h / FRAME_H);
		if (scale >= 1) scale = Math.floor(scale);
		const cw = Math.floor(FRAME_W * scale), ch = Math.floor(FRAME_H * scale);
		canvas.style.width = cw + "px"; canvas.style.height = ch + "px";
		canvas.style.left = Math.floor((w - cw) / 2) + "px"; canvas.style.top = Math.floor((h - ch) / 2) + "px";
	}
	addEventListener("resize", layout); layout();

	// ---- keyboard, as in FortuneHunterEventHandler.cpp. The logical key (e.key) is read before the physical code:
	// remote desktops can send wrong codes (see the vault's Gotchas).
	const KEYS_BY_KEY = { ArrowUp: "up", ArrowDown: "down", ArrowLeft: "left", ArrowRight: "right", Escape: "back", Enter: "start",
		" ": "green", z: "blue", Z: "blue", x: "yellow", X: "yellow", c: "red", C: "red", ",": "previous", ".": "next" };
	const KEYS_BY_CODE = { Numpad8: "up", Numpad2: "down", Numpad4: "left", Numpad6: "right", NumpadEnter: "start" };
	const send = (name) => { logInput("->", name); exports.platform_command(COMMAND[name]); };
	const gamepads = createGamepads(send, () => unlockAudio());
	const touch = createTouch(document.getElementById("screen"), send, () => unlockAudio());
	addEventListener("keydown", (e) => {
		const name = KEYS_BY_KEY[e.key] || (e.key === "Unidentified" ? KEYS_BY_CODE[e.code] : undefined);
		unlockAudio();
		if (!name) return; // held keys repeat, as they did under SDL
		e.preventDefault();
		logInput("key", e.key, e.code);
		send(name);
	});
	addEventListener("contextmenu", (e) => e.preventDefault());

	// ---- the frame loop ---------------------------------------------------------------------------------
	let prev = performance.now();
	function frame(now) {
		if (laidOutFor !== innerWidth + "x" + innerHeight) layout(); // a pane that was hidden at load reports 0 by 0
		gamepads.poll();
		if (scriptedKeys.length > 0) send(scriptedKeys.shift());
		exports.platform_frame(Math.min((now - prev) / 1000, 0.25), Date.now()); prev = now;
		const ptr = exports.platform_frame_ptr();
		if (ptr && exports.platform_frame_changed()) {
			ctx.putImageData(new ImageData(new Uint8ClampedArray(mem.memory.buffer, ptr, FRAME_W * FRAME_H * 4), FRAME_W, FRAME_H), 0, 0);
		}
		audio.update();
		const clipLen = exports.platform_clipboard_len();
		if (clipLen > 0) { // the About screen copies the author's page, as the original did
			const text = mem.loadString(exports.platform_clipboard_ptr(), clipLen);
			if (navigator.clipboard) navigator.clipboard.writeText(text).catch(() => {});
		}
		if (exports.platform_quit()) { // "Yes" on the quit screen: a page cannot close itself, so say goodbye
			document.body.insertAdjacentHTML("beforeend", '<div id="bye">Thanks for playing Fortune Hunter!<br>Reload the page to play again.</div>');
			return;
		}
		requestAnimationFrame(frame);
	}
	window.__platform = { exports, mem, audio, gamepads, touch, send };
	requestAnimationFrame(frame);
})();
