package game

// Saving the options and the statistics (Options.cpp, Statistics.cpp) as small JSON texts under namespaced keys (every
// itch.io HTML5 game shares one localStorage). Every field is validated on load; a bad text is ignored and the
// defaults stay.

import "core:encoding/json"
import "core:fmt"

OPTIONS_KEY :: "fh:options"
STATISTICS_KEY :: "fh:statistics"

// What the shipped config/options.json held.
DEFAULT_DIFFICULTY :: Difficulty.Normal
DEFAULT_OPTIONS :: Options{muted = false, sfx_volume = 64}

@(private)
read_int :: proc(o: json.Object, key: string, lo, hi: i64) -> (value: i64, ok: bool) {
	v, found := o[key]
	if !found { return }
	n, is_int := v.(json.Integer)
	if !is_int || n < lo || n > hi { return }
	return n, true
}

@(private)
read_object :: proc(core: ^Core, key: string) -> (object: json.Object, ok: bool) {
	if core.services.storage_get == nil { return }
	text, found := core.services.storage_get(key, context.temp_allocator)
	if !found { return }
	value, err := json.parse_string(text, .JSON, true, context.temp_allocator)
	if err != .None { return }
	object, ok = value.(json.Object)
	return
}

load_options :: proc(core: ^Core) {
	core.options = DEFAULT_OPTIONS
	core.game.difficulty = DEFAULT_DIFFICULTY
	parse_options(core)
}

@(private)
parse_options :: proc(core: ^Core) -> (ok: bool) {
	o := read_object(core, OPTIONS_KEY) or_return
	difficulty := read_int(o, "difficulty", 0, i64(len(Difficulty) - 1)) or_return
	sfx := read_int(o, "sfxVolume", 0, MAX_VOLUME) or_return
	muted, is_bool := o["muted"].(json.Boolean)
	if !is_bool { return }
	core.game.difficulty = Difficulty(difficulty)
	core.options = {muted = muted, sfx_volume = int(sfx)}
	return true
}

save_options :: proc(core: ^Core) {
	if core.services.storage_set == nil { return }
	text := fmt.tprintf(`{{"difficulty":%d,"muted":%t,"sfxVolume":%d}}`,
		int(core.game.difficulty), core.options.muted, core.options.sfx_volume)
	core.services.storage_set(OPTIONS_KEY, text)
}

SCORE_LIMIT :: 1_000_000_000_000

load_statistics :: proc(core: ^Core) {
	core.stats = {}
	parse_statistics(core)
}

@(private)
parse_statistics :: proc(core: ^Core) -> (ok: bool) {
	o := read_object(core, STATISTICS_KEY) or_return
	games := read_int(o, "gamesPlayed", 0, SCORE_LIMIT) or_return
	high := read_int(o, "highScore", 0, SCORE_LIMIT) or_return
	total := read_int(o, "totalScore", 0, SCORE_LIMIT) or_return
	core.stats = {games_played = games, high_score = high, total_score = total}
	return true
}

// Records a finished game. Like the original it reads the saved file first, so two tabs add up.
add_game :: proc(core: ^Core, score: int) {
	load_statistics(core)
	core.stats.total_score = min(core.stats.total_score + i64(score), SCORE_LIMIT)
	core.stats.games_played = min(core.stats.games_played + 1, SCORE_LIMIT)
	core.stats.high_score = max(core.stats.high_score, i64(score))
	if core.services.storage_set != nil {
		text := fmt.tprintf(`{{"gamesPlayed":%d,"highScore":%d,"totalScore":%d}}`,
			core.stats.games_played, core.stats.high_score, core.stats.total_score)
		core.services.storage_set(STATISTICS_KEY, text)
	}
}
