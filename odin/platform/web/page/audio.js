// Web Audio side of the core's sound output: decodes the effects the core lists and plays the ones the core asks for
// each step at gain volume / 128 (SDL_mixer's range). The core sends nothing while muted. Browsers only allow sound
// after a user gesture, so nothing plays before unlock() has been called from a key press, click or touch.
function createAudio(exports, mem) {
	const MAX_VOLUME = 128;
	const ctx = new (window.AudioContext || window.webkitAudioContext)();
	const sfxBuffers = [];
	let unlocked = false;
	const stats = { played: 0, loaded: 0, failed: 0 }; // for QA: window.__platform.audio.stats

	async function decode(path) {
		const response = await fetch(encodeURI(path));
		if (!response.ok) throw new Error("cannot load " + path);
		return await ctx.decodeAudioData(await response.arrayBuffer());
	}

	async function load() {
		const jobs = [];
		for (let id = 1; id < exports.platform_sound_count(); id++) { // 0 is None: no file
			const path = mem.loadString(exports.platform_sound_path_ptr(id), exports.platform_sound_path_len(id));
			jobs.push(decode(path).then((b) => { sfxBuffers[id] = b; stats.loaded++; }, (e) => { stats.failed++; console.warn(e); }));
		}
		await Promise.all(jobs);
	}

	function unlock() {
		if (unlocked) return;
		unlocked = true;
		ctx.resume().catch(() => {});
	}

	// Called every frame after the core has stepped.
	function update() {
		const n = exports.platform_sounds_len();
		if (n === 0 || !unlocked || ctx.state !== "running") return;
		const gainValue = exports.platform_sfx_volume() / MAX_VOLUME;
		const ids = new Uint8Array(mem.memory.buffer, exports.platform_sounds_ptr(), n);
		for (const id of ids) {
			const buffer = sfxBuffers[id];
			if (!buffer) continue;
			const source = ctx.createBufferSource();
			const gain = ctx.createGain();
			gain.gain.value = gainValue;
			source.buffer = buffer;
			source.connect(gain);
			gain.connect(ctx.destination);
			source.start();
			stats.played++;
		}
	}

	return { load, unlock, update, stats, context: ctx };
}
