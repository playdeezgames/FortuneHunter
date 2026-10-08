package game

// The core: owns everything, takes commands, draws the current screen. One core_step per presented frame.

Core :: struct {
	services:  Services,
	images:    [Image_Id]Image,
	frame:     Frame,
	canvas:    Canvas,
	seed:      u64,
	game:      Game,
	seeder:    Rng, // hands out a seed per new game
	ui:        Ui,
	options:   Options,
	stats:     Statistics,
}

core_init :: proc(core: ^Core, services: Services) {
	core.services = services
	canvas_init(&core.canvas, &core.frame)
	core.seed = services.entropy() if services.entropy != nil else 1
	rng_seed(&core.seeder, core.seed)
	core.ui = {state = .Main_Menu, menu = .Start, options = .Toggle_Mute, confirm = .No}
	load_options(core)
	load_statistics(core)
	free_all(context.temp_allocator) // the loaders parse into it
	if services.log != nil { services.log("Fortune Hunter core ready") }
}

core_step :: proc(core: ^Core, input: Step_Input, out: ^Step_Output) {
	for event in input.events { handle_command(core, event.command) }
	// sound effects: queued by the rules and the screens; nothing plays while muted
	sounds := take_sounds(&core.game)
	out.sounds = sounds if !core.options.muted else nil
	out.sfx_volume = core.options.sfx_volume
	draw_screen(core)
	out.frame = &core.frame
	out.frame_changed = true
	out.quit_requested = core.ui.state == .Quit
}
