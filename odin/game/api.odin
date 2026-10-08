package game

// The platform interface: everything the portable core exchanges with a platform.
// The core never imports a platform package; platforms never reach into core state.
//
//   platform -> core:  Input_Event list per frame, dt, the wall clock, decoded images (once, before the first step)
//   core -> platform:  Step_Output per frame (pixels, flags)
//
// Fixed geometry: the original's 640 by 480 window, shown with square pixels.

import "base:runtime"

FRAME_WIDTH :: 640
FRAME_HEIGHT :: 480

// The commands of the original (Command.h), in the same order, plus None.
Command :: enum u8 { None, Up, Down, Left, Right, Green, Red, Yellow, Blue, Next, Previous, Back, Start }

Input_Event :: struct {
	command: Command,
}

Step_Input :: struct {
	dt:     f64, // seconds since the previous step (presentation only)
	now_ms: f64, // wall clock, milliseconds since the Unix epoch; f64 because int is 32 bits on wasm
	events: []Input_Event,
}

Step_Output :: struct {
	frame:          ^[FRAME_WIDTH * FRAME_HEIGHT]u32, // bytes in memory order R,G,B,A (little-endian u32 0xAABBGGRR)
	frame_changed:  bool,
	quit_requested: bool,
	sounds:         []Sound_Id, // effects to play this step (empty while muted); valid until the next step
	sfx_volume:     int,        // 0 to 128
}

// Platform functions the core calls synchronously. Supplied once to core_init so the core has no platform imports
// and tests can pass fakes.
Services :: struct {
	entropy:        proc() -> u64, // for seeding; not reproducible
	log:            proc(message: string),
	storage_get:    proc(key: string, allocator: runtime.Allocator) -> (value: string, ok: bool),
	storage_set:    proc(key, value: string) -> bool, // false on quota or when storage is unavailable
	storage_remove: proc(key: string),
}

// The core's entry points are core_init and core_step (core.odin); images arrive through set_image (images.odin).
// core_step is called once per presented frame; it must not block, must not keep pointers into `input` after
// returning, and fills `out` completely every call.
_ :: runtime
