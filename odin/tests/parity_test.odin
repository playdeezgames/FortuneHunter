#+build !js
package tests

// The scripted game that tools/wasm_parity.js plays through the built wasm; both write the same digest and
// tools/test.sh requires them to be equal. The wasm has a 32-bit int and its own allocator; the game must not notice.
// The script presses every command (so every screen, a few full games, options and statistics get used), and the
// digest covers every frame, every sound effect, every clipboard request, and the saved text.

import "core:fmt"
import "core:os"
import "core:strconv"
import "core:testing"
import "fh:game"

parity_lcg: u32
parity_next :: proc() -> u32 {
	parity_lcg = parity_lcg * 1664525 + 1013904223
	return parity_lcg
}
fnv_word :: proc(h, word: u32) -> u32 { return (h ~ word) * 16777619 }

// Weighted so games get played: mostly arrows, some bombs, now and then menus.
// Phase A (first two thirds) is arrows and the green button only, so a hunter walks into zombies, dies, and Green
// carries on through the final score back into a new game; phase B uses every command.
parity_command :: proc(step, steps: int) -> game.Command {
	roll := (parity_next() >> 16) % 100
	if step < steps * 2 / 3 { return game.Command(1 + roll % 4) if roll < 85 else .Green }
	switch {
	case roll < 55: return game.Command(1 + roll % 4)          // up, down, left, right
	case roll < 70: return .Green
	case roll < 78: return .Start
	case roll < 86: return .Back
	case roll < 90: return .Next
	case roll < 94: return .Previous
	case roll < 97: return .Red
	case roll < 99: return .Blue
	}
	return .Yellow
}

@(test)
write_the_native_digest_for_the_wasm_parity_check :: proc(t: ^testing.T) {
	core := new_core_with_images(t)
	defer free_core(core)
	reset_storage()
	services := fake_services()
	services.entropy = proc() -> u64 { return 7 } // the node script's stub gives 7 too
	game.core_init(core, services)

	// the node script cannot decode PNGs: hand it the same pixels as raw RGBA files
	_ = os.make_directory("build/parity_images")
	for id in game.Image_Id {
		image := core.images[id]
		name := fmt.tprintf("build/parity_images/%d_%dx%d.rgba", int(id), image.width, image.height)
		_ = os.write_entire_file(name, (transmute([^]byte)raw_data(image.pixels))[:len(image.pixels) * 4])
	}

	steps := 6000
	if text := os.get_env("PARITY_STEPS", context.temp_allocator); text != "" { if n, ok := strconv.parse_int(text); ok { steps = n } }
	parity_lcg = 12345
	frames, sounds, clipboard := u32(2166136261), u32(2166136261), u32(2166136261)
	counts: [game.UI_State]int
	now := f64(1_790_000_000_000)
	for step in 0 ..< steps {
		// the first two presses pick hard difficulty (15 health), so random play finishes games
		event := game.Input_Event{command = parity_command(step, steps)}
		if step == 0 { event.command = .Down } else if step == 1 { event.command = .Green }
		now += 16
		out: game.Step_Output
		game.core_step(core, {dt = 0.016, now_ms = now, events = {event}}, &out)
		counts[core.ui.state] += 1
		if step % 5 == 0 { // every frame is hashed in full only every fifth step, the rest by sampling 64 pixels (node is slow)
			for pixel in out.frame { frames = fnv_word(frames, pixel) }
		} else {
			for i in 0 ..< 64 { frames = fnv_word(frames, out.frame[(i * 4813) % len(out.frame)]) }
		}
		for id in out.sounds { sounds = fnv_word(sounds, u32(id)) }
		sounds = fnv_word(sounds, u32(len(out.sounds)))
		for b in transmute([]u8)out.clipboard { clipboard = fnv_word(clipboard, u32(b)) }
		frames = fnv_word(frames, u32(out.sfx_volume) + (1 << 16 if out.quit_requested else 0))
		free_all(context.temp_allocator)
	}
	saved := u32(2166136261)
	for key in ([]string{game.OPTIONS_KEY, game.STATISTICS_KEY}) {
		for b in transmute([]u8)stored(key) { saved = fnv_word(saved, u32(b)) }
	}
	line := fmt.tprintf("frames=%d sounds=%d clipboard=%d saved=%d games=%d\n", frames, sounds, clipboard, saved, core.stats.games_played)
	testing.expect(t, os.write_entire_file("build/parity_native.txt", transmute([]byte)line) == nil)
	// the script must actually have visited the screens, or the comparison proves little
	for state in game.UI_State {
		if state == .Quit { continue }
		testing.expectf(t, counts[state] > 0, "the parity script never reached %v", state)
	}
	testing.expect(t, core.stats.games_played >= 1, "the parity script never finished a game")
}
