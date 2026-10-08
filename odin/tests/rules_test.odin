#+build !js
package tests

import "core:testing"
import "fh:game"

// An open 25 by 25 arena inside walls with the hunter at (10, 10), on easy difficulty.
arena :: proc() -> ^game.Game {
	g := new(game.Game)
	game.rng_seed(&g.rng, 1)
	for &cell in g.cells { cell.terrain = .Wall_NESW }
	for column in 3 ..< 28 {
		for row in 3 ..< 28 { g.cells[game.room_index(column, row)].terrain = .Floor }
	}
	g.has_hunter = true
	put(g, 10, 10, {kind = .Hunter})
	g.hunter.column, g.hunter.row = 10, 10
	game.update_room(g)
	return g
}

put :: proc(g: ^game.Game, column, row: int, object: game.Object) {
	g.cells[game.room_index(column, row)].object = object
}

at :: proc(g: ^game.Game, column, row: int) -> game.Cell {
	return g.cells[game.room_index(column, row)]
}

item :: proc(type: game.Item_Type) -> game.Object { return {kind = .Item, item = type} }
zombie :: proc(drop: Maybe(game.Item_Type) = nil) -> game.Object {
	d, has := drop.?
	return {kind = .Creature, creature = .Zombie, item = d if has else .Shield, has_drop = has}
}

sounds :: proc(g: ^game.Game) -> []game.Sound_Id { return game.take_sounds(g) }

@(test)
bumping_a_wall_costs_a_move_and_plays_the_bump :: proc(t: ^testing.T) {
	g := arena()
	defer free(g)
	g.hunter.column, g.hunter.row = 3, 10
	put(g, 10, 10, {})
	put(g, 3, 10, {kind = .Hunter})
	game.move_hunter(g, .West)
	testing.expect_value(t, g.hunter.column, 3)
	testing.expect_value(t, g.hunter.moves, 1)
	testing.expect_value(t, len(sounds(g)), 1)
	game.move_hunter(g, .West)
	s := sounds(g)
	testing.expect(t, len(s) == 1 && s[0] == .Bump_Wall)
}

@(test)
moving_updates_position_light_and_exploration :: proc(t: ^testing.T) {
	g := arena()
	defer free(g)
	game.move_hunter(g, .East)
	testing.expect_value(t, g.hunter.column, 11)
	testing.expect_value(t, at(g, 10, 10).object.kind, game.Object_Kind.None)
	testing.expect_value(t, at(g, 11, 10).object.kind, game.Object_Kind.Hunter)
	testing.expect(t, .Lit in at(g, 12, 11).flags && .Lit in at(g, 10, 9).flags)
	testing.expect(t, !(.Lit in at(g, 9, 10).flags), "left behind is no longer lit")
	testing.expect(t, .Explored in at(g, 9, 10).flags, "but stays explored")
	testing.expect(t, !(.Explored in at(g, 14, 10).flags))
}

@(test)
keys_open_locks_but_the_hunter_stays_put :: proc(t: ^testing.T) {
	g := arena()
	defer free(g)
	put(g, 11, 10, item(.Door_NS))
	put(g, 10, 11, item(.Key))
	game.move_hunter(g, .East) // locked
	s := sounds(g)
	testing.expect(t, len(s) == 1 && s[0] == .Door_Locked)
	testing.expect_value(t, g.hunter.column, 10)
	testing.expect_value(t, at(g, 11, 10).object.item, game.Item_Type.Door_NS)

	game.move_hunter(g, .South) // take the key
	testing.expect_value(t, g.hunter.keys, 1)
	game.move_hunter(g, .North)
	game.move_hunter(g, .East) // unlocks, does not move
	testing.expect_value(t, g.hunter.keys, 0)
	testing.expect_value(t, g.hunter.column, 10)
	testing.expect_value(t, at(g, 11, 10).object.kind, game.Object_Kind.None)
	game.move_hunter(g, .East)
	testing.expect_value(t, g.hunter.column, 11)
}

@(test)
exit_needs_the_exit_key_and_ends_the_game :: proc(t: ^testing.T) {
	g := arena()
	defer free(g)
	put(g, 11, 10, item(.Exit))
	game.move_hunter(g, .East)
	testing.expect_value(t, g.hunter.column, 10)
	testing.expect_value(t, len(sounds(g)), 0) // the exit has no failure sound
	g.hunter.exit_key = true
	game.move_hunter(g, .East)
	testing.expect(t, game.is_winner(g))
	testing.expect_value(t, g.hunter.column, 11)
	testing.expect(t, !game.can_continue(g))
	moves := g.hunter.moves
	game.move_hunter(g, .East)
	testing.expect_value(t, g.hunter.moves, moves) // a finished game ignores moves
}

@(test)
potions_heal_ten_shields_add_ten_up_to_the_maximum :: proc(t: ^testing.T) {
	g := arena()
	defer free(g)
	g.hunter.wounds = 15
	put(g, 11, 10, item(.Potion))
	game.move_hunter(g, .East)
	testing.expect_value(t, g.hunter.wounds, 5)
	put(g, 12, 10, item(.Potion))
	game.move_hunter(g, .East)
	testing.expect_value(t, g.hunter.wounds, 0)
	put(g, 13, 10, item(.Shield))
	game.move_hunter(g, .East)
	testing.expect_value(t, g.hunter.armor, 10)
	put(g, 14, 10, item(.Shield))
	game.move_hunter(g, .East)
	testing.expect_value(t, g.hunter.armor, 10) // easy maximum armor is 10 at level 0
}

@(test)
traps_wound_by_one_and_armor_soaks_it :: proc(t: ^testing.T) {
	g := arena()
	defer free(g)
	put(g, 11, 10, item(.Trap))
	put(g, 12, 10, item(.Trap))
	game.move_hunter(g, .East)
	testing.expect_value(t, g.hunter.wounds, 1)
	s := sounds(g)
	testing.expect(t, len(s) == 2 && s[0] == .Trap && s[1] == .Hit_Hunter, "trap sound, then the hunter's hurt sound")
	g.hunter.armor = 3
	game.move_hunter(g, .East)
	testing.expect_value(t, g.hunter.wounds, 1)
	testing.expect_value(t, g.hunter.armor, 2)
	testing.expect(t, g.hunter.hit, "armor soaking the damage still counts as a hit")
}

@(test)
upgrades_raise_the_maximums_and_scatter_traps :: proc(t: ^testing.T) {
	g := arena()
	defer free(g)
	put(g, 11, 10, item(.Health_Upgrade))
	put(g, 12, 10, item(.Attack_Upgrade))
	put(g, 13, 10, item(.Armor_Upgrade))
	testing.expect_value(t, game.max_health(g), 25)
	game.move_hunter(g, .East)
	testing.expect_value(t, game.max_health(g), 30)
	game.move_hunter(g, .East)
	testing.expect_value(t, game.max_attack(g), 8)
	game.move_hunter(g, .East)
	testing.expect_value(t, game.max_armor(g), 15)
	traps := 0
	for cell in g.cells { if cell.object.kind == .Item && cell.object.item == .Trap { traps += 1 } }
	testing.expect_value(t, traps, 25 + 50 + 10)
	// levels cap at the last entry
	g.hunter.health_level = 99
	testing.expect_value(t, game.max_health(g), 40)
}

@(test)
attacking_a_zombie_takes_several_hits_then_it_drops_its_item :: proc(t: ^testing.T) {
	g := arena()
	defer free(g)
	put(g, 11, 10, zombie(.Diamond))
	hits := 0
	for at(g, 11, 10).object.kind == .Creature && hits < 50 {
		game.move_hunter(g, .East)
		hits += 1
		testing.expect_value(t, g.hunter.column, 10) // attacking never moves him
	}
	testing.expect(t, hits >= 4 && hits <= 10, "10 health, 1 to 5 damage per hit on easy")
	testing.expect_value(t, at(g, 11, 10).object.kind, game.Object_Kind.Item)
	testing.expect_value(t, at(g, 11, 10).object.item, game.Item_Type.Diamond)
	game.move_hunter(g, .East)
	testing.expect_value(t, g.hunter.diamonds, 1)
}

@(test)
a_dead_zombie_without_a_drop_leaves_an_empty_cell :: proc(t: ^testing.T) {
	g := arena()
	defer free(g)
	put(g, 11, 10, zombie())
	for _ in 0 ..< 50 { game.move_hunter(g, .East); if at(g, 11, 10).object.kind != .Creature { break } }
	testing.expect_value(t, at(g, 11, 10).object.kind, game.Object_Kind.None)
}

@(test)
zombies_strike_from_beside_the_starting_cell_not_the_new_one :: proc(t: ^testing.T) {
	g := arena()
	defer free(g)
	put(g, 10, 9, zombie()) // north of the start: strikes after the hunter walks away east
	game.move_hunter(g, .East)
	testing.expect_value(t, g.hunter.wounds, 1)
	// a zombie beside the destination only is not adjacent to where the hunter started: no strike
	g2 := arena()
	defer free(g2)
	put(g2, 11, 9, zombie()) // diagonal to (10, 10), north of the destination (11, 10)
	game.move_hunter(g2, .East)
	testing.expect_value(t, g2.hunter.wounds, 0)
	game.move_hunter(g2, .South) // now (11, 11)... the zombie was adjacent to (11, 10), the start of this move
	testing.expect_value(t, g2.hunter.wounds, 1)
}

@(test)
zombie_at_the_start_strikes_even_when_the_hunter_bumps_a_wall :: proc(t: ^testing.T) {
	g := arena()
	defer free(g)
	g.hunter.column, g.hunter.row = 3, 10
	put(g, 10, 10, {})
	put(g, 3, 10, {kind = .Hunter})
	put(g, 3, 11, zombie())
	game.move_hunter(g, .West)
	testing.expect_value(t, g.hunter.wounds, 1)
}

@(test)
dying_stops_the_game_and_plays_the_death_sound :: proc(t: ^testing.T) {
	g := arena()
	defer free(g)
	g.hunter.wounds = game.max_health(g) - 1
	put(g, 10, 9, zombie())
	game.move_hunter(g, .East)
	testing.expect(t, !game.is_alive(g))
	testing.expect_value(t, g.hunter.wounds, game.max_health(g))
	s := sounds(g)
	testing.expect(t, len(s) == 1 && s[0] == .Dead_Hunter)
	testing.expect(t, !game.can_continue(g))
	game.use_bomb(g)
	testing.expect_value(t, len(sounds(g)), 0)
}

@(test)
bombs_hit_creatures_in_the_lit_area_only :: proc(t: ^testing.T) {
	g := arena()
	defer free(g)
	put(g, 11, 11, zombie(.Key))
	put(g, 12, 10, zombie()) // two away: not lit
	put(g, 9, 9, {kind = .Creature, creature = .Miniboss, item = .Armor_Upgrade, has_drop = true})
	game.use_bomb(g)
	testing.expect_value(t, game.bombs_left(g), 4)
	testing.expect_value(t, at(g, 11, 11).object.kind, game.Object_Kind.Item) // dead zombie dropped the key
	testing.expect_value(t, at(g, 12, 10).object.kind, game.Object_Kind.Creature)
	testing.expect_value(t, at(g, 12, 10).object.wounds, 0)
	testing.expect_value(t, at(g, 9, 9).object.wounds, 10) // minibosses have 20 health
	game.use_bomb(g)
	testing.expect_value(t, at(g, 9, 9).object.kind, game.Object_Kind.Item)
	testing.expect_value(t, at(g, 9, 9).object.item, game.Item_Type.Armor_Upgrade)
}

@(test)
running_out_of_bombs_plays_shucks :: proc(t: ^testing.T) {
	g := arena()
	defer free(g)
	g.difficulty = .Hard // one bomb
	game.use_bomb(g)
	_ = sounds(g)
	game.use_bomb(g)
	s := sounds(g)
	testing.expect(t, len(s) == 1 && s[0] == .Shucks)
	testing.expect_value(t, game.bombs_left(g), 0)
}

@(test)
score_adds_the_four_awards :: proc(t: ^testing.T) {
	g := arena()
	defer free(g)
	testing.expect_value(t, game.score(g), 25 * 50) // health only, easy
	g.hunter.diamonds = 3
	g.hunter.exit_key = true
	g.hunter.exited = true
	g.hunter.wounds = 5
	testing.expect_value(t, game.score(g), 3 * 500 + 20 * 50 + 250 + 2250)
	g.difficulty = .Hard
	testing.expect_value(t, game.score(g), 3 * 2000 + (15 - 5) * 200 + 1000 + 9000)
}

@(test)
difficulty_cycles_easy_normal_hard :: proc(t: ^testing.T) {
	g := new(game.Game)
	defer free(g)
	testing.expect_value(t, g.difficulty, game.Difficulty.Easy)
	game.next_difficulty(g); testing.expect_value(t, g.difficulty, game.Difficulty.Normal)
	game.next_difficulty(g); testing.expect_value(t, g.difficulty, game.Difficulty.Hard)
	game.next_difficulty(g); testing.expect_value(t, g.difficulty, game.Difficulty.Easy)
}

@(test)
attack_rolls_run_from_one_to_one_below_the_maximum :: proc(t: ^testing.T) {
	g := arena()
	defer free(g)
	g.difficulty = .Normal // max attack 4: rolls 1 to 3
	seen: [8]int
	for _ in 0 ..< 3000 { seen[game.attack_strength(g)] += 1 }
	testing.expect(t, seen[0] == 0 && seen[4] == 0, "never 0, never the maximum")
	testing.expect(t, seen[1] > 500 && seen[2] > 500 && seen[3] > 500)
}

@(test)
creature_health_level_is_tenths_of_health_rounded_down :: proc(t: ^testing.T) {
	z := zombie()
	testing.expect_value(t, game.creature_health_level(z), 10)
	z.wounds = 1; testing.expect_value(t, game.creature_health_level(z), 9)
	z.wounds = 9; testing.expect_value(t, game.creature_health_level(z), 1)
	z.wounds = 10; testing.expect_value(t, game.creature_health_level(z), 0)
	m := game.Object{kind = .Creature, creature = .Miniboss, wounds = 1}
	testing.expect_value(t, game.creature_health_level(m), 9) // 19 * 10 / 20
	m.wounds = 19
	testing.expect_value(t, game.creature_health_level(m), 0) // 1 * 10 / 20: the bar is empty with one hit point left
}

@(test)
the_sound_queue_is_bounded :: proc(t: ^testing.T) {
	g := new(game.Game)
	defer free(g)
	for _ in 0 ..< 100 { game.play_sound(g, .Ting) }
	testing.expect_value(t, len(game.take_sounds(g)), game.SOUND_QUEUE_SIZE)
	testing.expect_value(t, len(game.take_sounds(g)), 0)
}
