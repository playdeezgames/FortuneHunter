#+build js
package main

// Browser platform (js_wasm32). odin.js runs `main` once (init); then page/platform.js loads the images through the
// platform_image_* exports and calls `platform_frame` every animation frame. Everything crossing the boundary is a
// number, a (ptr, len) string, or a pointer into wasm memory.
import "base:runtime"
import "core:mem"
import "fh:game"

foreign import platform_env "platform"

@(default_calling_convention = "contextless")
foreign platform_env {
	js_entropy_u32 :: proc() -> u32 ---
	js_log :: proc(message: string) ---
}

core: ^game.Core // allocated once at start; never on the stack
out: game.Step_Output
events: [64]game.Input_Event
event_count: int
image_files := game.IMAGE_FILES
sound_files := game.SOUND_FILES

main :: proc() {
	core = new(game.Core)
	game.core_init(core, game.Services{
		entropy = proc() -> u64 {
			high := js_entropy_u32() // two statements: the order of the two calls in one expression is not guaranteed
			low := js_entropy_u32()
			return u64(high) << 32 | u64(low)
		},
		log = proc(message: string) { js_log(message) },
		storage_get = storage_get, storage_set = storage_set, storage_remove = storage_remove,
	})
}

// ---- exports called by page/platform.js ---------------------------------------------------------
@(export) platform_command :: proc "c" (command: i32) {
	if event_count < len(events) && command > 0 && command <= i32(max(game.Command)) {
		events[event_count] = {command = game.Command(command)}
		event_count += 1
	}
}
// now_ms is the wall clock in milliseconds (an f64: int is 32 bits here)
@(export) platform_frame :: proc "c" (dt, now_ms: f64) {
	context = runtime.default_context()
	if core == nil { return }
	game.core_step(core, {dt = dt, now_ms = now_ms, events = events[:event_count]}, &out)
	event_count = 0
	free_all(context.temp_allocator)
}
@(export) platform_frame_ptr :: proc "c" () -> rawptr { return out.frame }
@(export) platform_frame_changed :: proc "c" () -> bool { return out.frame_changed }
@(export) platform_quit :: proc "c" () -> bool { return out.quit_requested }

// Sound for the page's Web Audio shim: this step's effects (ids of game.Sound_Id; 0 is never sent) and the effects
// volume (0 to 128, SDL_mixer's range).
@(export) platform_sounds_ptr :: proc "c" () -> rawptr { return raw_data(out.sounds) }
@(export) platform_sounds_len :: proc "c" () -> i32 { return i32(len(out.sounds)) }
@(export) platform_sfx_volume :: proc "c" () -> i32 { return i32(out.sfx_volume) }

// Where the files are, so the list lives in one place (game/sound.odin).
@(export) platform_sound_count :: proc "c" () -> i32 { return i32(len(game.Sound_Id)) }
@(export) platform_sound_path_ptr :: proc "c" (id: i32) -> rawptr {
	if id < 0 || id >= i32(len(game.Sound_Id)) { return nil }
	return raw_data(sound_files[game.Sound_Id(id)].file)
}
@(export) platform_sound_path_len :: proc "c" (id: i32) -> i32 {
	if id < 0 || id >= i32(len(game.Sound_Id)) { return 0 }
	return i32(len(sound_files[game.Sound_Id(id)].file))
}

// The image table: the page asks which files to decode, so the list lives in one place (game/images.odin).
@(export) platform_image_count :: proc "c" () -> i32 { return i32(len(game.Image_Id)) }
@(export) platform_image_path_ptr :: proc "c" (id: i32) -> rawptr {
	if id < 0 || id >= i32(len(game.Image_Id)) { return nil }
	return raw_data(image_files[game.Image_Id(id)])
}
@(export) platform_image_path_len :: proc "c" (id: i32) -> i32 {
	if id < 0 || id >= i32(len(game.Image_Id)) { return 0 }
	return i32(len(image_files[game.Image_Id(id)]))
}
// The page asks for a buffer of width*height*4 bytes, fills it with RGBA, and hands it back; the core owns it then.
@(export) platform_alloc :: proc "c" (bytes: i32) -> rawptr {
	context = runtime.default_context()
	if bytes <= 0 { return nil }
	p, err := mem.alloc(int(bytes), 16)
	return p if err == nil else nil
}
@(export) platform_set_image :: proc "c" (id: i32, width, height: i32, pixels: rawptr) -> bool {
	context = runtime.default_context()
	if core == nil || pixels == nil || id < 0 || id >= i32(len(game.Image_Id)) || width <= 0 || height <= 0 { return false }
	return game.set_image(core, game.Image_Id(id), int(width), int(height), (cast([^]u32)pixels)[:int(width) * int(height)])
}
