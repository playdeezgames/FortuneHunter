package game

// The eight screens: what each command does (the *CommandProcessor classes) and how each is drawn (the *Renderer
// classes). Layout numbers are the original's. Text with a drop shadow is the black copy at (+4, +4) drawn first.

import "core:fmt"

MENU_TITLE :: "Welcome to Fortune Hunter!"
ABOUT_URL :: QR_URL // the text and the QR code on the About screen are the same link
QR_SCALE :: 3 // screen pixels per QR module

// ---- commands -------------------------------------------------------------------------------------------

handle_command :: proc(core: ^Core, command: Command) {
	g := &core.game
	ui := &core.ui
	switch ui.state {
	case .Main_Menu:
		#partial switch command {
		case .Up:   ui.menu = previous_menu_state(ui.menu)
		case .Down: ui.menu = next_menu_state(ui.menu)
		case .Green, .Start: main_menu_action(core)
		}
	case .Confirm_Quit:
		#partial switch command {
		case .Up, .Down: ui.confirm = .No if ui.confirm == .Yes else .Yes
		case .Back: ui.state = .Main_Menu
		case .Green: ui.state = .Quit if ui.confirm == .Yes else .Main_Menu
		}
	case .In_Play:
		#partial switch command {
		case .Back:
			if can_continue(g) { ui.state = .Main_Menu } else { go_to_final_score(core) }
		case .Up:    move_hunter(g, .North)
		case .Down:  move_hunter(g, .South)
		case .Left:  move_hunter(g, .West)
		case .Right: move_hunter(g, .East)
		case .Green:
			if can_continue(g) { use_bomb(g) } else { go_to_final_score(core) }
		}
	case .Options:
		options_command(core, command)
	case .About:
		#partial switch command {
		case .Green, .Back, .Start: ui.state = .Main_Menu
		}
	case .Instructions:
		#partial switch command {
		case .Green, .Back, .Start: ui.state = .Main_Menu
		case .Next, .Right: ui.help_page = (ui.help_page + 1) % HELP_PAGE_COUNT
		case .Previous, .Left: ui.help_page = (ui.help_page + HELP_PAGE_COUNT - 1) % HELP_PAGE_COUNT
		}
	case .Final_Score:
		#partial switch command {
		case .Green, .Start: ui.state = .Main_Menu
		}
	case .Statistics:
		#partial switch command {
		case .Red, .Green, .Back: ui.state = .Main_Menu
		}
	case .Quit:
	}
}

@(private)
go_to_final_score :: proc(core: ^Core) {
	add_game(core, score(&core.game))
	core.ui.state = .Final_Score
}

@(private)
main_menu_action :: proc(core: ^Core) {
	ui := &core.ui
	g := &core.game
	switch ui.menu {
	case .Quit: ui.state = .Confirm_Quit
	case .Difficulty:
		if !can_continue(g) {
			next_difficulty(g)
			save_options(core)
		}
	case .Start:
		if !can_continue(g) { start_game(g, rng_next(&core.seeder)) }
		ui.state = .In_Play
	case .Options:
		ui.state = .Options
		ui.options = .Toggle_Mute // the screen always opens on its first item (the original opened on Main Menu)
	case .About: ui.state = .About
	case .Statistics: ui.state = .Statistics
	case .Instructions: ui.state = .Instructions
	}
}

@(private)
options_command :: proc(core: ^Core, command: Command) {
	ui := &core.ui
	o := &core.options
	change_volume :: proc(volume: ^int, delta: int) { volume^ = clamp(volume^ + delta, 0, MAX_VOLUME) }
	#partial switch command {
	case .Up:   ui.options = previous_options_state(ui.options)
	case .Down: ui.options = next_options_state(ui.options)
	case .Left, .Right:
		delta := VOLUME_STEP if command == .Right else -VOLUME_STEP
		#partial switch ui.options {
		case .Sfx_Volume:
			change_volume(&o.sfx_volume, delta)
			play_sound(&core.game, .Hit_Hunter) // the sample sound
			save_options(core)
		}
	case .Green:
		#partial switch ui.options {
		case .Toggle_Mute:
			o.muted = !o.muted
			save_options(core)
		case .Back: ui.state = .Main_Menu
		}
	case .Back: ui.state = .Main_Menu
	}
}

// ---- drawing --------------------------------------------------------------------------------------------

draw_screen :: proc(core: ^Core) {
	canvas := &core.canvas
	if !all_images_loaded(core) {
		fill_canvas(canvas, rgba(32, 0, 48)) // waiting for the page to hand over the images
		return
	}
	switch core.ui.state {
	case .Main_Menu:    draw_main_menu(core)
	case .Confirm_Quit: draw_confirm_quit(core)
	case .In_Play:      draw_in_play(core)
	case .Options:      draw_options(core)
	case .About:        draw_about(core)
	case .Instructions: draw_instructions(core)
	case .Final_Score:  draw_final_score(core)
	case .Statistics:   draw_statistics(core)
	case .Quit:         fill_canvas(canvas, rgba(0, 0, 0))
	}
}

@(private)
background :: proc(core: ^Core, id: Image_Id) { draw_image(&core.canvas, core.images[id], 0, 0) }

@(private)
draw_main_menu :: proc(core: ^Core) {
	canvas := &core.canvas
	background(core, .Bg_Main_Menu)
	draw_text_shadowed(core, canvas, 320, 76, MENU_TITLE, .Light_Green, centered = true)
	g := &core.game
	items: [7]string
	items[0] = "Continue" if can_continue(g) else "Start"
	items[1] = hunter_descriptor(g).name
	items[2] = "Instructions"
	items[3] = "Statistics"
	items[4] = "About"
	items[5] = "Options"
	items[6] = "Quit"
	for text, line in items {
		selected := int(core.ui.menu) == line
		draw_text_shadowed(core, canvas, 320, 168 + 24 * line, text, .Yellow if selected else .White, centered = true)
	}
}

@(private)
draw_confirm_quit :: proc(core: ^Core) {
	canvas := &core.canvas
	background(core, .Bg_Confirm_Quit)
	draw_text_shadowed(core, canvas, 320, 120, "Are you sure you want to quit?", .Red, centered = true)
	items := [2]Confirm_State{.No, .Yes}
	names := [2]string{"No", "Yes"}
	for state, line in items {
		draw_text_shadowed(core, canvas, 320, 208 + 64 * line, names[line], .Yellow if core.ui.confirm == state else .Gray, centered = true)
	}
}

@(private)
draw_in_play :: proc(core: ^Core) {
	canvas := &core.canvas
	background(core, .Bg_In_Play)
	draw_room_panel(core, canvas, &core.game)
	draw_status_panel(core, canvas, &core.game)
}

STATUS_PANEL_CLIP :: Rect{480, 0, 160, 480}

// The seven statistics down the right edge (StatusPanelRenderer): an icon, then the number, one 16 pixel line each.
@(private)
draw_status_panel :: proc(core: ^Core, canvas: ^Canvas, g: ^Game) {
	set_clip(canvas, STATUS_PANEL_CLIP)
	x := STATUS_PANEL_CLIP.x
	line :: proc(core: ^Core, canvas: ^Canvas, row: int, icon: Sprite_Id, text: string) {
		draw_sprite(core, canvas, icon, STATUS_PANEL_CLIP.x, row * CELL_SIZE)
		draw_text(core, canvas, STATUS_PANEL_CLIP.x + CELL_SIZE, row * CELL_SIZE, text, .White)
	}
	line(core, canvas, 0, .Move_Icon, fmt.tprint(g.hunter.moves))
	line(core, canvas, 1, .Diamond_Item, fmt.tprint(g.hunter.diamonds))
	line(core, canvas, 2, .Sword_Item, fmt.tprintf("1d%d", max_attack(g)))
	line(core, canvas, 3, .Shield_Item, fmt.tprintf("%d/%d", g.hunter.armor, max_armor(g)))
	line(core, canvas, 4, .Potion_Item, fmt.tprintf("%d/%d", health(g), max_health(g)))
	line(core, canvas, 5, .Key_Item, fmt.tprint(g.hunter.keys))
	line(core, canvas, 6, .Bombs, fmt.tprint(bombs_left(g)))
	if !is_alive(g) {
		draw_text(core, canvas, x, 112, "Yer dead!", .Red)
	} else if is_winner(g) {
		draw_text(core, canvas, x, 112, "You win!", .Light_Green)
	}
	clear_clip(canvas)
}

@(private)
draw_options :: proc(core: ^Core) {
	canvas := &core.canvas
	o := core.options
	background(core, .Bg_Options)
	draw_text_shadowed(core, canvas, 8, 80, "              ==Options==", .Light_Green)
	percent :: proc(volume: int) -> int { return volume * 100 / MAX_VOLUME }
	items: [3]string
	items[0] = "     Unmute" if o.muted else "      Mute"
	items[1] = fmt.tprintf("SFX Volume(%d%%)", percent(o.sfx_volume))
	items[2] = "    Main Menu"
	for text, line in items {
		draw_text_shadowed(core, canvas, 12 * 16, 240 - 4 * 16 + 32 * line, text, .Yellow if int(core.ui.options) == line else .White)
	}
}

@(private)
draw_about :: proc(core: ^Core) {
	canvas := &core.canvas
	background(core, .Bg_About)
	draw_text_shadowed(core, canvas, 320, 160, "==About Fortune Hunter==", .Light_Green, centered = true)
	draw_qr(canvas, 320, 188, QR_SCALE)
	draw_text_shadowed(core, canvas, 320, 320, "A Production of TheGrumpyGameDev", .Gray, centered = true)
	draw_text_shadowed(core, canvas, 320, 336, ABOUT_URL, .Light_Blue, centered = true)
}

@(private)
draw_instructions :: proc(core: ^Core) {
	canvas := &core.canvas
	background(core, .Bg_Instructions)
	pages := HELP_PAGES
	for label in pages[core.ui.help_page].labels {
		if label.shadow {
			draw_text(core, canvas, label.x + label.shadow_x, label.y + label.shadow_y, label.text, label.shadow_color)
		}
		draw_text(core, canvas, label.x, label.y, label.text, label.color)
	}
}

AWARD_NAMES :: [Hunter_Award]string{.Diamond = "Diamonds", .Health = "Health", .Exit_Key = "Exit Key", .Exit = "Exited"}

@(private)
draw_final_score :: proc(core: ^Core) {
	canvas := &core.canvas
	g := &core.game
	background(core, .Bg_Final_Score)
	draw_text_shadowed(core, canvas, 320, 96, "==Final Score==", .Green, centered = true)
	names := AWARD_NAMES
	awards := hunter_descriptor(g).awards
	y := 192
	for award in Hunter_Award {
		tally := score_tally(g, award)
		text := fmt.tprintf("%s x%d -> %d", names[award], tally, tally * awards[award])
		draw_text_shadowed(core, canvas, 320, y, text, .Gray, centered = true)
		y += 24
	}
	y += 32
	draw_text_shadowed(core, canvas, 320, y, fmt.tprintf("Total Score: %d", score(g)), .Cyan, centered = true)
}

@(private)
draw_statistics :: proc(core: ^Core) {
	canvas := &core.canvas
	s := core.stats
	background(core, .Bg_Statistics)
	draw_text_shadowed(core, canvas, 320, 96, "==Statistics==", .Green, centered = true)
	draw_text_shadowed(core, canvas, 320, 208, fmt.tprintf("Games Played: %d", s.games_played), .Gray, centered = true)
	draw_text_shadowed(core, canvas, 320, 240, fmt.tprintf("High Score: %d", s.high_score), .Gray, centered = true)
	draw_text_shadowed(core, canvas, 320, 272, fmt.tprintf("Average Score: %d", average_score(s)), .Gray, centered = true)
}
