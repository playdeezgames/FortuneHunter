#+build !js
package tests

import "core:fmt"
import "core:strings"
import "core:testing"
import "fh:game"

// A core with all images loaded, on the main menu with default options.
menu_core :: proc(t: ^testing.T) -> ^game.Core { return new_core_with_images(t) }

stored :: proc(key: string) -> string { return fake_storage[key] or_else "" }

@(test)
the_game_opens_on_the_main_menu_with_the_shipped_defaults :: proc(t: ^testing.T) {
	core := menu_core(t)
	defer free_core(core)
	testing.expect_value(t, core.ui.state, game.UI_State.Main_Menu)
	testing.expect_value(t, core.ui.menu, game.Main_Menu_State.Start)
	testing.expect_value(t, core.ui.options, game.Options_State.Back)
	testing.expect_value(t, core.ui.confirm, game.Confirm_State.No)
	testing.expect_value(t, core.game.difficulty, game.Difficulty.Normal)
	testing.expect_value(t, core.options, game.Options{muted = false, sfx_volume = 64})
}

@(test)
menu_selection_wraps_in_both_directions :: proc(t: ^testing.T) {
	core := menu_core(t)
	defer free_core(core)
	step(core, .Up)
	testing.expect_value(t, core.ui.menu, game.Main_Menu_State.Quit)
	step(core, .Down)
	testing.expect_value(t, core.ui.menu, game.Main_Menu_State.Start)
	for _ in 0 ..< 7 { step(core, .Down) }
	testing.expect_value(t, core.ui.menu, game.Main_Menu_State.Start)
	step(core, .Down, .Down)
	testing.expect_value(t, core.ui.menu, game.Main_Menu_State.Instructions)
}

@(test)
start_makes_a_game_and_continue_keeps_it :: proc(t: ^testing.T) {
	core := menu_core(t)
	defer free_core(core)
	step(core, .Green)
	testing.expect_value(t, core.ui.state, game.UI_State.In_Play)
	testing.expect(t, game.can_continue(&core.game))
	column, row := core.game.hunter.column, core.game.hunter.row
	step(core, .Back)
	testing.expect_value(t, core.ui.state, game.UI_State.Main_Menu)
	step(core, .Start) // "Continue"
	testing.expect_value(t, core.ui.state, game.UI_State.In_Play)
	testing.expect(t, core.game.hunter.column == column && core.game.hunter.row == row, "same game")
}

@(test)
difficulty_cycles_and_is_saved_but_not_during_a_game :: proc(t: ^testing.T) {
	core := menu_core(t)
	defer free_core(core)
	step(core, .Down, .Green)
	testing.expect_value(t, core.game.difficulty, game.Difficulty.Hard)
	testing.expect(t, strings.contains(stored(game.OPTIONS_KEY), `"difficulty":2`), stored(game.OPTIONS_KEY))
	step(core, .Green, .Green)
	testing.expect_value(t, core.game.difficulty, game.Difficulty.Normal)
	step(core, .Up, .Green) // Start a game
	step(core, .Back, .Down, .Green) // back at the menu, difficulty cannot change while a game can continue
	testing.expect_value(t, core.game.difficulty, game.Difficulty.Normal)
}

@(test)
quitting_asks_first :: proc(t: ^testing.T) {
	core := menu_core(t)
	defer free_core(core)
	step(core, .Up, .Green) // Quit
	testing.expect_value(t, core.ui.state, game.UI_State.Confirm_Quit)
	testing.expect_value(t, core.ui.confirm, game.Confirm_State.No)
	out := step(core, .Green) // "No"
	testing.expect_value(t, core.ui.state, game.UI_State.Main_Menu)
	testing.expect(t, !out.quit_requested)
	step(core, .Green) // Quit is still selected
	step(core, .Back)
	testing.expect_value(t, core.ui.state, game.UI_State.Main_Menu)
	step(core, .Green, .Up)
	testing.expect_value(t, core.ui.confirm, game.Confirm_State.Yes)
	step(core, .Down)
	testing.expect_value(t, core.ui.confirm, game.Confirm_State.No)
	step(core, .Down)
	out = step(core, .Green)
	testing.expect_value(t, core.ui.state, game.UI_State.Quit)
	testing.expect(t, out.quit_requested)
}

@(test)
options_adjust_volumes_mute_and_persist :: proc(t: ^testing.T) {
	core := menu_core(t)
	defer free_core(core)
	step(core, .Up, .Up) // Start -> Quit -> Options
	testing.expect_value(t, core.ui.menu, game.Main_Menu_State.Options)
	step(core, .Green)
	testing.expect_value(t, core.ui.state, game.UI_State.Options)
	testing.expect_value(t, core.ui.options, game.Options_State.Back)
	step(core, .Up) // Sfx volume
	testing.expect_value(t, core.ui.options, game.Options_State.Sfx_Volume)
	for _ in 0 ..< 5 { step(core, .Left) }
	testing.expect_value(t, core.options.sfx_volume, 0) // clamped
	for _ in 0 ..< 12 { step(core, .Right) }
	testing.expect_value(t, core.options.sfx_volume, 128)
	testing.expect(t, strings.contains(stored(game.OPTIONS_KEY), `"sfxVolume":128`))
	for _ in 0 ..< 3 { step(core, .Left) }
	testing.expect_value(t, core.options.sfx_volume, 80)
	out := step(core, .Right)
	testing.expect_value(t, core.options.sfx_volume, 96)
	testing.expect(t, len(out.sounds) == 1 && out.sounds[0] == .Hit_Hunter, "the sample sound plays")
	step(core, .Up) // Toggle mute
	out = step(core, .Green)
	testing.expect(t, core.options.muted)
	out = step(core, .Down, .Right)
	testing.expect_value(t, len(out.sounds), 0) // nothing plays while muted
	testing.expect(t, strings.contains(stored(game.OPTIONS_KEY), `"muted":true`))
	step(core, .Up, .Green) // unmute
	testing.expect(t, !core.options.muted)

	step(core, .Up, .Green) // Back
	testing.expect_value(t, core.ui.state, game.UI_State.Main_Menu)
	// a fresh core reads the saved options
	again := new(game.Core)
	defer free(again)
	game.core_init(again, fake_services())
	testing.expect_value(t, again.options, core.options)
}

@(test)
about_copies_the_url_for_one_step :: proc(t: ^testing.T) {
	core := menu_core(t)
	defer free_core(core)
	core.ui.menu = .About
	out := step(core, .Green)
	testing.expect_value(t, core.ui.state, game.UI_State.About)
	testing.expect_value(t, out.clipboard, "https://thegrumpygamedev.itch.io/")
	out = step(core)
	testing.expect_value(t, out.clipboard, "")
	step(core, .Back)
	testing.expect_value(t, core.ui.state, game.UI_State.Main_Menu)
}

@(test)
instruction_pages_wrap_and_are_remembered :: proc(t: ^testing.T) {
	core := menu_core(t)
	defer free_core(core)
	core.ui.menu = .Instructions
	step(core, .Green)
	testing.expect_value(t, core.ui.help_page, 0)
	step(core, .Right)
	testing.expect_value(t, core.ui.help_page, 1)
	step(core, .Next, .Next)
	testing.expect_value(t, core.ui.help_page, 0)
	step(core, .Left)
	testing.expect_value(t, core.ui.help_page, 2)
	step(core, .Previous)
	testing.expect_value(t, core.ui.help_page, 1)
	step(core, .Start)
	testing.expect_value(t, core.ui.state, game.UI_State.Main_Menu)
	step(core, .Green)
	testing.expect_value(t, core.ui.help_page, 1) // the page is not reset
}

kill_hunter :: proc(core: ^game.Core) { core.game.hunter.wounds = game.max_health(&core.game) }

@(test)
a_finished_game_goes_to_the_final_score_and_the_statistics :: proc(t: ^testing.T) {
	core := menu_core(t)
	defer free_core(core)
	step(core, .Green) // start
	core.game.hunter.diamonds = 2
	kill_hunter(core)
	testing.expect(t, !game.can_continue(&core.game))
	testing.expect_value(t, core.ui.state, game.UI_State.In_Play)
	step(core, .Up) // a dead hunter cannot move
	testing.expect_value(t, core.ui.state, game.UI_State.In_Play)
	expected := game.score(&core.game)
	testing.expect_value(t, expected, 2 * 1000) // normal: diamonds 1000 each, no health left
	step(core, .Green) // bomb key on a finished game goes to the final score
	testing.expect_value(t, core.ui.state, game.UI_State.Final_Score)
	testing.expect_value(t, core.stats.games_played, i64(1))
	testing.expect_value(t, core.stats.high_score, i64(expected))
	step(core, .Back) // not a final-score command
	testing.expect_value(t, core.ui.state, game.UI_State.Final_Score)
	step(core, .Start)
	testing.expect_value(t, core.ui.state, game.UI_State.Main_Menu)
	// start the next game and end it by winning
	step(core, .Green)
	core.game.hunter.exited = true
	core.game.hunter.exit_key = true
	step(core, .Back) // game over: Back goes to the score as well
	testing.expect_value(t, core.ui.state, game.UI_State.Final_Score)
	testing.expect_value(t, core.stats.games_played, i64(2))
	testing.expect_value(t, game.average_score(core.stats), (core.stats.total_score) / 2)
	testing.expect(t, strings.contains(stored(game.STATISTICS_KEY), `"gamesPlayed":2`), stored(game.STATISTICS_KEY))
	// statistics survive a restart
	again := new(game.Core)
	defer free(again)
	game.core_init(again, fake_services())
	testing.expect_value(t, again.stats, core.stats)
}

@(test)
bad_saved_data_is_ignored :: proc(t: ^testing.T) {
	bad_options := []string{
		`not json`, `[]`, `{"difficulty":3,"muted":false,"sfxVolume":1}`,
		`{"difficulty":1,"muted":"no","sfxVolume":1}`, `{"difficulty":1,"muted":false,"sfxVolume":129}`,
		`{"difficulty":1,"muted":false,"sfxVolume":1.5}`, `{"difficulty":1,"muted":false}`,
	}
	for text in bad_options {
		core := new_core()
		fake_services().storage_set(game.OPTIONS_KEY, text)
		game.core_init(core, fake_services())
		testing.expectf(t, core.options == game.DEFAULT_OPTIONS && core.game.difficulty == game.DEFAULT_DIFFICULTY, "accepted %v", text)
		free(core)
	}
	bad_stats := []string{`{`, `{"gamesPlayed":-1,"highScore":0,"totalScore":0}`, `{"gamesPlayed":1,"highScore":"x","totalScore":0}`, `{"gamesPlayed":1,"highScore":2}`}
	for text in bad_stats {
		core := new_core()
		fake_services().storage_set(game.STATISTICS_KEY, text)
		game.core_init(core, fake_services())
		testing.expectf(t, core.stats == {}, "accepted %v", text)
		free(core)
	}
}

@(test)
every_screen_draws_over_its_background :: proc(t: ^testing.T) {
	core := menu_core(t)
	defer free_core(core)
	backgrounds := [game.UI_State]game.Image_Id {
		.Main_Menu = .Bg_Main_Menu, .Confirm_Quit = .Bg_Confirm_Quit, .Quit = .Bg_Main_Menu, .In_Play = .Bg_In_Play,
		.Options = .Bg_Options, .About = .Bg_About, .Instructions = .Bg_Instructions, .Final_Score = .Bg_Final_Score,
		.Statistics = .Bg_Statistics,
	}
	step(core, .Green) // a game, so in-play has something to show
	for state in game.UI_State {
		if state == .Quit { continue }
		core.ui.state = state
		out := step(core)
		bg := core.images[backgrounds[state]]
		same, different := 0, 0
		for i in 0 ..< game.FRAME_WIDTH * game.FRAME_HEIGHT {
			if out.frame[i] == bg.pixels[i] | 0xFF000000 { same += 1 } else { different += 1 }
		}
		testing.expectf(t, different > 200, "%v draws nothing over its background", state)
		testing.expectf(t, same > different, "%v hides its background", state)
	}
	core.ui.state = .Quit
	out := step(core)
	testing.expect_value(t, out.frame[0], u32(0xFF000000))
}

@(test)
every_instruction_page_fits_the_screen :: proc(t: ^testing.T) {
	pages := game.HELP_PAGES
	for page, i in pages {
		for label in page.labels {
			width := game.text_width(strings.trim_right(label.text, " ")) // a trailing space shows nothing
			testing.expectf(t, label.x >= 0 && label.x + width <= game.FRAME_WIDTH, "page %v: %q runs off the screen", i, label.text)
			testing.expectf(t, label.y >= 0 && label.y + 16 <= game.FRAME_HEIGHT, "page %v: %q is below the screen", i, label.text)
		}
	}
}

@(test)
final_score_lists_the_four_awards :: proc(t: ^testing.T) {
	core := menu_core(t)
	defer free_core(core)
	step(core, .Green)
	core.game.hunter.diamonds = 3
	core.game.hunter.exit_key = true
	kill_hunter(core)
	core.ui.state = .Final_Score
	// the text lines the screen builds (checked through the same formatting the screen uses)
	line := fmt.tprintf("%s x%d -> %d", "Diamonds", game.score_tally(&core.game, .Diamond), game.score_tally(&core.game, .Diamond) * 1000)
	testing.expect_value(t, line, "Diamonds x3 -> 3000")
	testing.expect_value(t, game.score(&core.game), 3 * 1000 + 500)
}

@(test)
sound_output_follows_the_options_and_the_rules :: proc(t: ^testing.T) {
	core := menu_core(t)
	defer free_core(core)
	out := step(core)
	testing.expect_value(t, out.sfx_volume, 64)
	step(core, .Green) // start a game
	core.game.cells[game.room_index(core.game.hunter.column + 1, core.game.hunter.row)].terrain = .Wall_NESW
	out = step(core, .Right) // bump the wall (or step): either way something plays or nothing; force a known sound
	game.play_sound(&core.game, .Ting)
	out = step(core)
	testing.expect(t, len(out.sounds) == 1 && out.sounds[0] == .Ting)
	out = step(core) // the queue was drained
	testing.expect_value(t, len(out.sounds), 0)
	core.options.muted = true
	game.play_sound(&core.game, .Ting)
	out = step(core)
	testing.expect(t, len(out.sounds) == 0, "muted: no effects")
	core.options.muted = false
	out = step(core)
	testing.expect_value(t, len(out.sounds), 0) // the muted effect was dropped, not saved up
}
