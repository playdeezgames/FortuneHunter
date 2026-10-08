package game

// The rules (GameData, Hunter, Creature, Item): one level, the hunter, and the moves he can make. No rendering, no
// platform. Randomness comes from `rng`, and sound effects are queued in `sounds` for the platform to play.

Hunter :: struct {
	column, row:  int,
	keys:         int,
	moves:        int,
	wounds:       int,
	armor:        int,
	diamonds:     int,
	exit_key:     bool,
	exited:       bool,
	hit:          bool, // struck by the last move (even if armor soaked it all)
	bombs_used:   int,
	health_level: int, // upgrades collected
	attack_level: int,
	armor_level:  int,
}

SOUND_QUEUE_SIZE :: 32

Game :: struct {
	rng:         Rng,
	cells:       [ROOM_COLUMNS * ROOM_ROWS]Cell,
	hunter:      Hunter,
	has_hunter:  bool, // false until the first game is started
	difficulty:  Difficulty,
	sounds:      [SOUND_QUEUE_SIZE]Sound_Id,
	sound_count: int,
}

play_sound :: proc(g: ^Game, id: Sound_Id) {
	if id == .None || g.sound_count >= len(g.sounds) { return }
	g.sounds[g.sound_count] = id
	g.sound_count += 1
}

// Returns the queued sound effects and empties the queue; valid until the next play_sound.
take_sounds :: proc(g: ^Game) -> []Sound_Id {
	n := g.sound_count
	g.sound_count = 0
	return g.sounds[:n]
}

cell_at :: proc(g: ^Game, column, row: int) -> ^Cell {
	if !room_in_bounds(column, row) { return nil }
	return &g.cells[room_index(column, row)]
}

hunter_descriptor :: proc(g: ^Game) -> Hunter_Descriptor {
	table := HUNTER_DESCRIPTORS
	return table[g.difficulty]
}

@(private)
level_value :: proc(levels: [LEVELS]int, level: int) -> int {
	return levels[min(level, LEVELS - 1)]
}

max_health :: proc(g: ^Game) -> int { return level_value(hunter_descriptor(g).max_healths, g.hunter.health_level) }
max_attack :: proc(g: ^Game) -> int { return level_value(hunter_descriptor(g).max_attacks, g.hunter.attack_level) }
max_armor :: proc(g: ^Game) -> int { return level_value(hunter_descriptor(g).max_armors, g.hunter.armor_level) }
health :: proc(g: ^Game) -> int { return max_health(g) - g.hunter.wounds }
bombs_left :: proc(g: ^Game) -> int { return hunter_descriptor(g).initial_bombs - g.hunter.bombs_used }
is_alive :: proc(g: ^Game) -> bool { return health(g) > 0 }
is_winner :: proc(g: ^Game) -> bool { return g.hunter.exited }
can_continue :: proc(g: ^Game) -> bool { return g.has_hunter && is_alive(g) && !is_winner(g) }

next_difficulty :: proc(g: ^Game) { g.difficulty = hunter_descriptor(g).next_difficulty }

// A hit rolls 1 to max, as the status panel's "1dN" says. (The original rolled 1 to max - 1; the user chose to make
// the label true. See docs/QUIRKS.md.)
attack_strength :: proc(g: ^Game) -> int {
	return rng_range(&g.rng, 1, max(max_attack(g), 1) + 1)
}

hunter_add_wounds :: proc(g: ^Game, amount: int) {
	amount := amount
	// As in the original, any strike counts as a hit, even one the armor absorbs completely, so the hurt sound plays
	// (the user tried silent absorbed hits and reverted; a dedicated armor sound is a TODO, see docs/QUIRKS.md).
	if amount > 0 { g.hunter.hit = true }
	absorbed := min(g.hunter.armor, amount)
	amount -= absorbed
	g.hunter.armor -= absorbed
	g.hunter.wounds = min(g.hunter.wounds + amount, max_health(g))
}

score_tally :: proc(g: ^Game, award: Hunter_Award) -> int {
	switch award {
	case .Diamond:  return g.hunter.diamonds
	case .Health:   return health(g)
	case .Exit_Key: return 1 if g.hunter.exit_key else 0
	case .Exit:     return 1 if g.hunter.exited else 0
	}
	return 0
}

score :: proc(g: ^Game) -> int {
	if !g.has_hunter { return 0 }
	awards := hunter_descriptor(g).awards
	total := 0
	for award in Hunter_Award { total += score_tally(g, award) * awards[award] }
	return total
}

// ---- starting a game ------------------------------------------------------------------------------

MAX_GENERATION_TRIES :: 50

// Builds a new level and places the hunter. False only if no level could be generated (it does not happen with the
// shipped content; see the generator tests), in which case there is no game.
start_game :: proc(g: ^Game, seed: u64) -> bool {
	rng_seed(&g.rng, seed)
	g.has_hunter = false
	for _ in 0 ..< MAX_GENERATION_TRIES {
		if generate_room(&g.cells, &g.rng) && place_hunter(g) {
			g.has_hunter = true
			update_room(g)
			return true
		}
	}
	return false
}

@(private)
place_hunter :: proc(g: ^Game) -> bool {
	g.hunter = {}
	for _ in 0 ..< MAX_PLACEMENT_TRIES {
		column := rng_below(&g.rng, ROOM_COLUMNS)
		row := rng_below(&g.rng, ROOM_ROWS)
		cell := cell_at(g, column, row)
		if cell.terrain == .Floor && cell.object.kind == .None {
			cell.object = {kind = .Hunter}
			g.hunter.column, g.hunter.row = column, row
			return true
		}
	}
	return false
}

// ---- light and exploration ----------------------------------------------------------------------

update_room :: proc(g: ^Game) {
	for &cell in g.cells { cell.flags -= {.Lit} }
	for column in g.hunter.column - 1 ..= g.hunter.column + 1 {
		for row in g.hunter.row - 1 ..= g.hunter.row + 1 {
			if cell := cell_at(g, column, row); cell != nil { cell.flags += {.Lit, .Explored} }
		}
	}
}

// ---- combat -------------------------------------------------------------------------------------

@(private)
damage_creature :: proc(g: ^Game, cell: ^Cell, damage: int) {
	creatures := CREATURE_DESCRIPTORS
	creature := &cell.object
	d := creatures[creature.creature]
	creature.wounds += damage
	if creature.wounds >= d.health {
		play_sound(g, d.death_sfx)
		// The creature is gone and its drop (if any) lies in its place. (The original freed the drop together with
		// the creature and then used it; see docs/QUIRKS.md. The intent is what is implemented.)
		cell.object = {kind = .Item, item = creature.item} if creature.has_drop else {}
	} else {
		play_sound(g, d.damage_sfx)
	}
}

@(private)
resolve_attacks_on_hunter :: proc(g: ^Game, adjacent: [4][2]int, count: int) {
	creatures := CREATURE_DESCRIPTORS
	for i in 0 ..< count {
		column, row := adjacent[i][0], adjacent[i][1]
		if column == g.hunter.column && row == g.hunter.row { continue }
		cell := cell_at(g, column, row)
		if cell.object.kind == .Creature {
			hunter_add_wounds(g, creatures[cell.object.creature].attack_strength)
		}
	}
	if g.hunter.hit {
		d := hunter_descriptor(g)
		play_sound(g, d.damage_sfx if is_alive(g) else d.death_sfx)
	}
}

// ---- items ------------------------------------------------------------------------------------

@(private)
can_pick_up :: proc(g: ^Game, item: Item_Type) -> bool {
	#partial switch item {
	case .Exit:               return g.hunter.exit_key
	case .Door_EW, .Door_NS:  return g.hunter.keys > 0
	}
	return true
}

@(private)
pick_up :: proc(g: ^Game, item: Item_Type) {
	h := &g.hunter
	#partial switch item {
	case .Door_EW, .Door_NS: h.keys = max(h.keys - 1, 0)
	case .Key:               h.keys += 1
	case .Exit_Key:          h.exit_key = true
	case .Diamond:           h.diamonds += 1
	case .Potion:            h.wounds = max(h.wounds - 10, 0)
	case .Shield:            h.armor = min(h.armor + 10, max_armor(g))
	case .Exit:              h.exited = true
	case .Trap:              hunter_add_wounds(g, 1)
	case .Armor_Upgrade:     h.armor_level += 1
	case .Attack_Upgrade:    h.attack_level += 1
	case .Health_Upgrade:    h.health_level += 1
	}
}

// Scatters traps (or whatever an item spawns) over empty cells of the allowed terrain: gives up after 50 failures in a
// row, as the original did.
@(private)
spawn_items :: proc(g: ^Game, item: Item_Type, count: int) {
	descriptors := ITEM_DESCRIPTORS
	d := descriptors[item]
	remaining, failures := count, 0
	for remaining > 0 && failures < 50 {
		failures += 1
		cell := &g.cells[rng_below(&g.rng, len(g.cells))]
		if cell.object.kind == .None && cell.terrain in d.spawn_terrains {
			cell.object = {kind = .Item, item = item}
			failures = 0
			remaining -= 1
		}
	}
}

// True if the hunter may now move into the cell.
@(private)
attempt_to_pick_up :: proc(g: ^Game, cell: ^Cell) -> bool {
	descriptors := ITEM_DESCRIPTORS
	item := cell.object.item
	d := descriptors[item]
	if !can_pick_up(g, item) {
		play_sound(g, d.failure_sfx)
		return false
	}
	pick_up(g, item)
	play_sound(g, d.pick_up_sfx)
	if d.spawn_count > 0 { spawn_items(g, d.spawn_item, d.spawn_count) }
	cell.object = {}
	return !d.stops_movement
}

// ---- moves ---------------------------------------------------------------------------------------

move_hunter :: proc(g: ^Game, direction: Direction) {
	if !g.has_hunter { return }
	g.hunter.hit = false
	if !is_alive(g) || is_winner(g) { return }

	column, row := g.hunter.column, g.hunter.row
	// The neighbours that may strike back are those of the cell the hunter starts in (see docs/QUIRKS.md).
	adjacent: [4][2]int
	adjacent_count := 0
	for d in Direction {
		dc, dr := direction_delta(d)
		if room_in_bounds(column + dc, row + dr) {
			adjacent[adjacent_count] = {column + dc, row + dr}
			adjacent_count += 1
		}
	}

	dc, dr := direction_delta(direction)
	next := cell_at(g, column + dc, row + dr)
	if next != nil && is_floor(next.terrain) {
		complete := true
		switch next.object.kind {
		case .Creature:
			damage_creature(g, next, attack_strength(g))
			complete = false
		case .Item:
			complete = attempt_to_pick_up(g, next)
		case .Hunter, .None:
		}
		if complete {
			cell_at(g, column, row).object = {}
			next.object = {kind = .Hunter}
			g.hunter.column, g.hunter.row = column + dc, row + dr
		}
	} else {
		play_sound(g, .Bump_Wall)
	}
	resolve_attacks_on_hunter(g, adjacent, adjacent_count)
	g.hunter.moves += 1
	update_room(g)
}

use_bomb :: proc(g: ^Game) {
	if !can_continue(g) { return }
	d := hunter_descriptor(g)
	if g.hunter.bombs_used < d.initial_bombs {
		g.hunter.bombs_used += 1
		play_sound(g, d.bomb_sfx)
		for &cell in g.cells {
			if .Lit in cell.flags && cell.object.kind == .Creature { damage_creature(g, &cell, d.bomb_damage) }
		}
	} else {
		play_sound(g, d.no_bomb_sfx)
	}
}
