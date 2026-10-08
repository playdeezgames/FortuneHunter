#+build !js
package tests

import "base:runtime"
import "core:bytes"
import "core:fmt"
import "core:strings"
import "core:image/png"
import "core:testing"
import "fh:game"

// Working directory when testing is the repo root; the original game's assets are still where they were.
ASSET_ROOT :: "FortuneHunter/FortuneHunter/"

// Loads a PNG the way the page does: RGBA, straight alpha. The caller owns the pixels.
load_image :: proc(path: string) -> (width, height: int, pixels: []u32, ok: bool) {
	img, err := png.load_from_file(path, {.alpha_add_if_missing})
	if err != nil || img == nil { return }
	defer png.destroy(img)
	if img.channels != 4 || img.depth != 8 { return }
	width, height = img.width, img.height
	data := bytes.buffer_to_bytes(&img.pixels)
	pixels = make([]u32, width * height)
	for i in 0 ..< len(pixels) {
		pixels[i] = u32(data[i * 4]) | u32(data[i * 4 + 1]) << 8 | u32(data[i * 4 + 2]) << 16 | u32(data[i * 4 + 3]) << 24
	}
	return width, height, pixels, true
}

// A fake browser storage shared by the tests (they run on one thread): reset it with `reset_storage`.
fake_storage: map[string]string

reset_storage :: proc() {
	context.allocator = runtime.heap_allocator() // the fake lives across tests: keep it out of their leak checks
	for k, v in fake_storage { delete(k); delete(v) }
	clear(&fake_storage)
}

fake_services :: proc() -> game.Services {
	return {
		entropy = proc() -> u64 { return 42 },
		storage_get = proc(key: string, allocator: runtime.Allocator) -> (string, bool) {
			v, ok := fake_storage[key]
			return strings.clone(v, allocator) if ok else "", ok
		},
		storage_set = proc(key, value: string) -> bool {
			context.allocator = runtime.heap_allocator()
			if key in fake_storage {
				old_key, old_value := delete_key(&fake_storage, key)
				delete(old_key); delete(old_value)
			}
			fake_storage[strings.clone(key)] = strings.clone(value)
			return true
		},
		storage_remove = proc(key: string) {
			context.allocator = runtime.heap_allocator()
			if key in fake_storage {
				old_key, old_value := delete_key(&fake_storage, key)
				delete(old_key); delete(old_value)
			}
		},
	}
}

new_core :: proc() -> ^game.Core {
	reset_storage()
	core := new(game.Core)
	game.core_init(core, fake_services())
	return core
}

// A core with every image handed over, as the page does.
new_core_with_images :: proc(t: ^testing.T) -> ^game.Core {
	core := new_core()
	files := game.IMAGE_FILES
	for id in game.Image_Id {
		width, height, pixels, ok := load_image(fmt.tprint(ASSET_ROOT, files[id], sep = ""))
		testing.expectf(t, ok && game.set_image(core, id, width, height, pixels), "could not hand over %v", id)
	}
	return core
}

free_core :: proc(core: ^game.Core) {
	for image in core.images { delete(image.pixels) }
	free(core)
}

step :: proc(core: ^game.Core, commands: ..game.Command) -> game.Step_Output {
	events := make([dynamic]game.Input_Event, context.temp_allocator)
	for c in commands { append(&events, game.Input_Event{command = c}) }
	out: game.Step_Output
	game.core_step(core, {dt = 1.0 / 60, now_ms = 0, events = events[:]}, &out)
	return out
}

@(test)
every_image_file_loads_with_expected_size :: proc(t: ^testing.T) {
	files := game.IMAGE_FILES
	for id in game.Image_Id {
		path := files[id]
		full := fmt.tprint(ASSET_ROOT, path, sep = "")
		width, height, pixels, ok := load_image(full)
		defer delete(pixels)
		testing.expectf(t, ok, "cannot load %v", full)
		if !ok { continue }
		#partial switch id {
		case .Font:  testing.expect_value(t, width, 256); testing.expect_value(t, height, 256)
		case .Tiles: testing.expect_value(t, width, 128); testing.expect_value(t, height, 80)
		case:        testing.expect_value(t, width, 640); testing.expect_value(t, height, 480)
		}
	}
}

@(test)
set_image_rejects_wrong_sizes_and_core_hands_over_a_frame :: proc(t: ^testing.T) {
	core := new_core()
	defer free_core(core)
	px := make([]u32, 4)
	defer delete(px)
	testing.expect(t, !game.set_image(core, .Font, 3, 3, px), "size mismatch must be rejected")
	testing.expect(t, !game.set_image(core, .Font, 0, 0, nil), "empty must be rejected")
	testing.expect(t, !game.all_images_loaded(core))

	out := step(core)
	testing.expect(t, out.frame != nil && out.frame_changed)
	testing.expect_value(t, core.seed, u64(42))
}
