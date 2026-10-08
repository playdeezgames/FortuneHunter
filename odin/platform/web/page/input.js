// Gamepad and touch input. Both only turn physical input into command names ("up", "green", ...) and hand them to
// `send`; the game decides what a command means. Keyboard is handled in platform.js.

// ---- gamepad -------------------------------------------------------------------------------------------
// The browser's "standard" layout, mapped like FortuneHunterEventHandler.cpp maps SDL's controller buttons:
// A green, B red, X blue, Y yellow, shoulders previous/next, Back back, Start start, d-pad arrows. Like the original,
// the sticks are ignored and a button press is one command (no auto-repeat).
const GAMEPAD_BUTTONS = { 0: "green", 1: "red", 2: "blue", 3: "yellow", 4: "previous", 5: "next", 8: "back", 9: "start",
	12: "up", 13: "down", 14: "left", 15: "right" };

function createGamepads(send, onPress) {
	const down = new Map(); // gamepad index -> array of previous button states
	const input = { getPads: () => (navigator.getGamepads ? navigator.getGamepads() : []) };
	// Call once per frame: sends a command for every button that went down since the last call.
	input.poll = function () {
		const seen = new Set();
		for (const pad of input.getPads()) {
			if (!pad || !pad.connected || pad.mapping !== "standard") continue; // other layouts have unknown buttons
			seen.add(pad.index);
			const before = down.get(pad.index) || [];
			const now = [];
			pad.buttons.forEach((button, i) => {
				now[i] = button.pressed;
				if (button.pressed && !before[i] && GAMEPAD_BUTTONS[i]) { onPress(); send(GAMEPAD_BUTTONS[i]); }
			});
			down.set(pad.index, now);
		}
		for (const index of [...down.keys()]) if (!seen.has(index)) down.delete(index);
	};
	return input;
}

// ---- touch ---------------------------------------------------------------------------------------------
// On-screen controls (a d-pad and A / Back / Start) appear once the page sees a touch, or with ?touch=1. Dragging a
// finger on the picture also steps: every 28 screen pixels in the dominant direction is one arrow press. Arrows
// repeat while held, as held keys do.
const REPEAT_DELAY_MS = 400, REPEAT_INTERVAL_MS = 130, SWIPE_STEP_PX = 28;

function createTouch(canvas, send, onPress) {
	const style = document.createElement("style");
	style.textContent = `
		.pad { position: fixed; bottom: 14px; display: none; gap: 8px; z-index: 5; touch-action: none; user-select: none; -webkit-user-select: none; }
		.pad.shown { display: grid; }
		#pad-left { left: 14px; grid-template-columns: repeat(3, 56px); grid-template-rows: repeat(3, 56px); }
		#pad-right { right: 14px; grid-template-columns: 72px 72px; grid-template-rows: 72px 40px; align-items: stretch; }
		.pad button { font: bold 18px monospace; color: #ddd; background: rgba(60,60,70,.55); border: 2px solid rgba(200,200,210,.55);
			border-radius: 12px; padding: 0; touch-action: none; -webkit-tap-highlight-color: transparent; }
		.pad button.down { background: rgba(240,220,90,.6); color: #000; }
		#pad-right .wide { grid-column: span 2; }`;
	document.head.appendChild(style);

	const make = (id, items) => {
		const el = document.createElement("div");
		el.className = "pad"; el.id = id;
		for (const item of items) {
			const b = document.createElement("button");
			b.textContent = item.label; b.setAttribute("aria-label", item.name || "");
			if (item.style) b.style.cssText = item.style;
			if (item.cls) b.className = item.cls;
			if (!item.name) { b.disabled = true; b.style.visibility = "hidden"; }
			else attachButton(b, item.name, item.repeat);
			el.appendChild(b);
		}
		document.body.appendChild(el);
		return el;
	};

	function attachButton(button, name, repeat) {
		let delay = null, interval = null;
		const stop = () => { clearTimeout(delay); clearInterval(interval); delay = interval = null; button.classList.remove("down"); };
		button.addEventListener("pointerdown", (e) => {
			e.preventDefault(); e.stopPropagation();
			try { button.setPointerCapture(e.pointerId); } catch (err) { /* a synthetic pointer: nothing to capture */ }
			button.classList.add("down");
			onPress(); send(name);
			if (repeat) delay = setTimeout(() => { interval = setInterval(() => send(name), REPEAT_INTERVAL_MS); }, REPEAT_DELAY_MS);
		});
		for (const type of ["pointerup", "pointercancel", "lostpointercapture"]) button.addEventListener(type, stop);
		button.addEventListener("contextmenu", (e) => e.preventDefault());
	}

	const left = make("pad-left", [
		{}, { label: "▲", name: "up", repeat: true }, {},
		{ label: "◀", name: "left", repeat: true }, {}, { label: "▶", name: "right", repeat: true },
		{}, { label: "▼", name: "down", repeat: true }, {},
	]);
	const right = make("pad-right", [
		{ label: "Back", name: "back" }, { label: "A", name: "green" },
		{ label: "Start", name: "start", cls: "wide" },
	]);

	const touch = { shown: false };
	touch.show = function () {
		if (touch.shown) return;
		touch.shown = true;
		left.classList.add("shown"); right.classList.add("shown");
	};
	if (new URLSearchParams(location.search).has("touch") || (matchMedia && matchMedia("(pointer: coarse)").matches)) touch.show();

	// Drag on the picture to walk. Several fingers: the first one steers.
	let steer = null; // { id, x, y }
	canvas.addEventListener("pointerdown", (e) => {
		e.preventDefault();
		if (e.pointerType === "touch") touch.show();
		if (steer === null) steer = { id: e.pointerId, x: e.clientX, y: e.clientY };
	});
	canvas.addEventListener("pointermove", (e) => {
		if (steer === null || e.pointerId !== steer.id) return;
		for (;;) {
			const dx = e.clientX - steer.x, dy = e.clientY - steer.y;
			if (Math.max(Math.abs(dx), Math.abs(dy)) < SWIPE_STEP_PX) return;
			const horizontal = Math.abs(dx) >= Math.abs(dy);
			send(horizontal ? (dx > 0 ? "right" : "left") : (dy > 0 ? "down" : "up"));
			if (horizontal) steer.x += Math.sign(dx) * SWIPE_STEP_PX; else steer.y += Math.sign(dy) * SWIPE_STEP_PX;
		}
	});
	const release = (e) => { if (steer !== null && e.pointerId === steer.id) steer = null; };
	canvas.addEventListener("pointerup", release);
	canvas.addEventListener("pointercancel", release);
	return touch;
}
