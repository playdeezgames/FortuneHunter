package game

// Screens and their menu states (UIState.h, MainMenuState, OptionsState, ConfirmState). Each menu's "next" and
// "previous" move round a cycle in the order the original's tables give.

UI_State :: enum u8 { Main_Menu, Confirm_Quit, Quit, In_Play, Options, About, Instructions, Final_Score, Statistics }

Main_Menu_State :: enum u8 { Start, Difficulty, Instructions, Statistics, About, Options, Quit }
Options_State :: enum u8 { Toggle_Mute, Sfx_Volume, Back }
Confirm_State :: enum u8 { Yes, No }

next_menu_state :: proc "contextless" (s: Main_Menu_State) -> Main_Menu_State {
	return Main_Menu_State((int(s) + 1) % len(Main_Menu_State))
}
previous_menu_state :: proc "contextless" (s: Main_Menu_State) -> Main_Menu_State {
	return Main_Menu_State((int(s) + len(Main_Menu_State) - 1) % len(Main_Menu_State))
}
next_options_state :: proc "contextless" (s: Options_State) -> Options_State {
	return Options_State((int(s) + 1) % len(Options_State))
}
previous_options_state :: proc "contextless" (s: Options_State) -> Options_State {
	return Options_State((int(s) + len(Options_State) - 1) % len(Options_State))
}

MAX_VOLUME :: 128 // SDL_mixer's range, which the saved options use
VOLUME_STEP :: 16

Options :: struct {
	muted:      bool,
	sfx_volume: int,
}

Statistics :: struct {
	games_played: i64,
	high_score:   i64,
	total_score:  i64,
}

average_score :: proc(s: Statistics) -> i64 {
	return s.total_score / s.games_played if s.games_played > 0 else 0
}

Ui :: struct {
	state:      UI_State,
	menu:       Main_Menu_State,
	options:    Options_State,
	confirm:    Confirm_State,
	help_page:  int,
}
