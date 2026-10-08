#+build !js
package tests

import "core:testing"
import "fh:game"

SEEDS :: 150

rooms_for_seeds :: proc(count: int) -> []^game.Game {
	rooms := make([]^game.Game, count)
	for i in 0 ..< count {
		rooms[i] = new(game.Game)
		rooms[i].difficulty = game.Difficulty(i % 3)
	}
	return rooms
}

free_rooms :: proc(rooms: []^game.Game) {
	for g in rooms { free(g) }
	delete(rooms)
}

@(test)
every_seed_generates_a_level_on_the_first_try :: proc(t: ^testing.T) {
	rng: game.Rng
	cells := new([game.ROOM_COLUMNS * game.ROOM_ROWS]game.Cell)
	defer free(cells)
	for seed in 0 ..< 400 {
		game.rng_seed(&rng, u64(seed))
		testing.expectf(t, game.generate_room(cells, &rng), "seed %v needed a retry", seed)
	}
}

@(test)
mazes_are_connected_with_exactly_the_loops_added :: proc(t: ^testing.T) {
	rng: game.Rng
	for seed in 0 ..< 200 {
		game.rng_seed(&rng, u64(seed))
		maze: game.Maze
		game.generate_maze(&maze, &rng)
		open := 0
		for c in 0 ..< game.MAZE_COLUMNS {
			for r in 0 ..< game.MAZE_ROWS {
				if game.maze_door_open(&maze, c, r, .East) { open += 1 }
				if game.maze_door_open(&maze, c, r, .South) { open += 1 }
			}
		}
		testing.expect_value(t, open, game.MAZE_COLUMNS * game.MAZE_ROWS - 1) // a spanning tree
		testing.expect_value(t, reachable_maze_cells(&maze), game.MAZE_COLUMNS * game.MAZE_ROWS)
		testing.expect_value(t, game.loopify_maze(&maze, &rng, game.LOOPIFICATIONS), game.LOOPIFICATIONS)
		testing.expect_value(t, reachable_maze_cells(&maze), game.MAZE_COLUMNS * game.MAZE_ROWS)
	}
}

reachable_maze_cells :: proc(maze: ^game.Maze) -> int {
	seen: [game.MAZE_COLUMNS * game.MAZE_ROWS]bool
	stack: [game.MAZE_COLUMNS * game.MAZE_ROWS]int
	count, top := 0, 0
	seen[0] = true
	stack[0] = 0
	top = 1
	for top > 0 {
		top -= 1
		cell := stack[top]
		count += 1
		c, r := cell % game.MAZE_COLUMNS, cell / game.MAZE_COLUMNS
		for d in game.Direction {
			dc, dr := game.direction_delta(d)
			n := (c + dc) + (r + dr) * game.MAZE_COLUMNS
			if game.maze_door_open(maze, c, r, d) && !seen[n] {
				seen[n] = true
				stack[top] = n
				top += 1
			}
		}
	}
	return count
}

@(test)
the_same_seed_gives_the_same_level_and_other_seeds_differ :: proc(t: ^testing.T) {
	a, b, c := new(game.Game), new(game.Game), new(game.Game)
	defer { free(a); free(b); free(c) }
	testing.expect(t, game.start_game(a, 7) && game.start_game(b, 7) && game.start_game(c, 8))
	testing.expect(t, a.cells == b.cells && a.hunter == b.hunter)
	testing.expect(t, a.cells != c.cells)
}

@(test)
terrain_follows_the_maze_and_walls_join_their_neighbours :: proc(t: ^testing.T) {
	rooms := rooms_for_seeds(SEEDS)
	defer free_rooms(rooms)
	for g, seed in rooms {
		testing.expect(t, game.start_game(g, u64(seed)))
		for column in 0 ..< game.ROOM_COLUMNS {
			for row in 0 ..< game.ROOM_ROWS {
				cell := g.cells[game.room_index(column, row)]
				if column % 2 == 1 && row % 2 == 1 {
					testing.expect(t, game.is_floor(cell.terrain), "every maze cell is floor")
				} else if column % 2 == 0 && row % 2 == 0 && game.is_floor(cell.terrain) {
					// the original turns a pillar whose four sides are all open into floor (docs/QUIRKS.md)
					for d in game.Direction {
						dc, dr := game.direction_delta(d)
						n := game.cell_at(g, column + dc, row + dr)
						testing.expect(t, n != nil && game.is_floor(n.terrain), "a floor pillar is surrounded by floor")
					}
				}
				if game.is_floor(cell.terrain) { continue }
				if next_to_floor_pillar(g, column, row) { continue } // smoothing is sequential: such cells may predate it
				sides := 0
				for d in game.Direction {
					dc, dr := game.direction_delta(d)
					n := game.cell_at(g, column + dc, row + dr)
					if n == nil || !game.is_floor(n.terrain) { sides += 1 << uint(d) }
				}
				names := [16]game.Terrain_Type{
					.Floor, .Wall_N, .Wall_E, .Wall_NE, .Wall_S, .Wall_NS, .Wall_ES, .Wall_NES,
					.Wall_W, .Wall_NW, .Wall_EW, .Wall_NEW, .Wall_SW, .Wall_NSW, .Wall_ESW, .Wall_NESW,
				}
				testing.expect_value(t, cell.terrain, names[sides])
			}
		}
		// the border is all wall
		for column in 0 ..< game.ROOM_COLUMNS {
			testing.expect(t, !game.is_floor(g.cells[game.room_index(column, 0)].terrain))
			testing.expect(t, !game.is_floor(g.cells[game.room_index(column, game.ROOM_ROWS - 1)].terrain))
		}
	}
}

next_to_floor_pillar :: proc(g: ^game.Game, column, row: int) -> bool {
	for d in game.Direction {
		dc, dr := game.direction_delta(d)
		n := game.cell_at(g, column + dc, row + dr)
		if n != nil && (column + dc) % 2 == 0 && (row + dr) % 2 == 0 && game.is_floor(n.terrain) { return true }
	}
	return false
}

Counts :: struct {
	shields, potions, traps, keys, doors, exits, exit_keys, diamonds, zombies, minibosses: int,
	upgrades:                                                                   [3]int,
	dead_ends:                                                                  int,
}

count_level :: proc(g: ^game.Game) -> (c: Counts) {
	count_item :: proc(c: ^Counts, i: game.Item_Type) {
		#partial switch i {
		case .Shield: c.shields += 1
		case .Potion: c.potions += 1
		case .Trap: c.traps += 1
		case .Key: c.keys += 1
		case .Door_NS, .Door_EW: c.doors += 1
		case .Exit: c.exits += 1
		case .Exit_Key: c.exit_keys += 1
		case .Diamond: c.diamonds += 1
		case .Health_Upgrade: c.upgrades[0] += 1
		case .Attack_Upgrade: c.upgrades[1] += 1
		case .Armor_Upgrade: c.upgrades[2] += 1
		}
	}
	for cell in g.cells {
		if cell.terrain == .Floor_Dead_End { c.dead_ends += 1 }
		#partial switch cell.object.kind {
		case .Item: count_item(&c, cell.object.item)
		case .Creature:
			if cell.object.creature == .Zombie { c.zombies += 1 } else { c.minibosses += 1 }
			if cell.object.has_drop { count_item(&c, cell.object.item) }
		}
	}
	return
}

@(test)
levels_contain_exactly_what_the_descriptors_ask_for :: proc(t: ^testing.T) {
	rooms := rooms_for_seeds(SEEDS)
	defer free_rooms(rooms)
	for g, seed in rooms {
		testing.expect(t, game.start_game(g, u64(seed + 1000)))
		c := count_level(g)
		testing.expect(t, c.dead_ends >= 11, "enough dead ends for the exit, exit key and nine upgrades")
		testing.expect_value(t, c.shields, 30)
		testing.expect_value(t, c.potions, 20)
		testing.expect_value(t, c.traps, 30)
		testing.expect_value(t, c.keys, c.dead_ends)
		testing.expect_value(t, c.doors, c.dead_ends)
		testing.expect_value(t, c.exits, 1)
		testing.expect_value(t, c.exit_keys, 1)
		testing.expect_value(t, c.upgrades, [3]int{3, 3, 3})
		testing.expect_value(t, c.minibosses, 9)
		testing.expect_value(t, c.zombies, 100)
		testing.expect_value(t, c.diamonds, c.dead_ends - 11)
	}
}

@(test)
everything_stands_on_terrain_it_may_spawn_on :: proc(t: ^testing.T) {
	rooms := rooms_for_seeds(SEEDS)
	defer free_rooms(rooms)
	items := game.ITEM_DESCRIPTORS
	creatures := game.CREATURE_DESCRIPTORS
	for g, seed in rooms {
		testing.expect(t, game.start_game(g, u64(seed + 2000)))
		hunters := 0
		for cell in g.cells {
			switch cell.object.kind {
			case .None:
			case .Hunter:
				hunters += 1
				testing.expect_value(t, cell.terrain, game.Terrain_Type.Floor)
			case .Item:
				testing.expectf(t, cell.terrain in items[cell.object.item].spawn_terrains, "%v on %v", cell.object.item, cell.terrain)
			case .Creature:
				testing.expect(t, cell.terrain in creatures[cell.object.creature].spawn_terrains)
				if cell.object.has_drop && cell.object.creature == .Zombie {
					testing.expect(t, items[cell.object.item].object_type in creatures[.Zombie].spawn_objects)
				}
			}
		}
		testing.expect_value(t, hunters, 1)
		testing.expect(t, g.cells[game.room_index(g.hunter.column, g.hunter.row)].object.kind == .Hunter)
		for cell in g.cells { testing.expect(t, cell.terrain != .Floor_Dead_End || cell.object.kind != .None, "no empty dead end") }
	}
}

@(test)
every_dead_end_is_sealed_by_exactly_one_lock :: proc(t: ^testing.T) {
	rooms := rooms_for_seeds(SEEDS)
	defer free_rooms(rooms)
	for g, seed in rooms {
		testing.expect(t, game.start_game(g, u64(seed + 3000)))
		for column in 0 ..< game.ROOM_COLUMNS {
			for row in 0 ..< game.ROOM_ROWS {
				if g.cells[game.room_index(column, row)].terrain != .Floor_Dead_End { continue }
				floors := 0
				for d in game.Direction {
					dc, dr := game.direction_delta(d)
					n := game.cell_at(g, column + dc, row + dr)
					if n == nil || !game.is_floor(n.terrain) { continue }
					floors += 1
					testing.expect_value(t, n.object.kind, game.Object_Kind.Item)
					want := game.Item_Type.Door_NS if d == .East || d == .West else game.Item_Type.Door_EW
					testing.expect_value(t, n.object.item, want)
				}
				testing.expect_value(t, floors, 1)
			}
		}
	}
}

// Greedy play: flood from the hunter through anything but locks (creatures can be killed), collect keys, spend them
// on adjacent locks, repeat. Every cell with an object must end up reachable and the key supply must never run out.
@(test)
every_level_can_be_cleared_with_the_keys_in_it :: proc(t: ^testing.T) {
	rooms := rooms_for_seeds(SEEDS)
	defer free_rooms(rooms)
	for g, seed in rooms {
		testing.expect(t, game.start_game(g, u64(seed + 4000)))
		reached := make([]bool, len(g.cells))
		defer delete(reached)
		stack := make([dynamic]int)
		defer delete(stack)
		append(&stack, game.room_index(g.hunter.column, g.hunter.row))
		reached[stack[0]] = true
		keys := 0
		pending_locks := make([dynamic]int) // locks next to the reached area, not yet opened
		defer delete(pending_locks)
		for {
			for len(stack) > 0 {
				i := pop(&stack)
				cell := g.cells[i]
				if cell.object.kind == .Item && cell.object.item == .Key { keys += 1 }
				if cell.object.kind == .Creature && cell.object.has_drop && cell.object.item == .Key { keys += 1 }
				for d in game.Direction {
					dc, dr := game.direction_delta(d)
					column, row := i % game.ROOM_COLUMNS + dc, i / game.ROOM_COLUMNS + dr
					if !game.room_in_bounds(column, row) { continue }
					n := game.room_index(column, row)
					if reached[n] || !game.is_floor(g.cells[n].terrain) { continue }
					reached[n] = true
					o := g.cells[n].object
					if o.kind == .Item && (o.item == .Door_NS || o.item == .Door_EW) {
						append(&pending_locks, n)
					} else {
						append(&stack, n)
					}
				}
			}
			if keys > 0 && len(pending_locks) > 0 {
				keys -= 1
				append(&stack, pop(&pending_locks))
			} else { break }
		}
		testing.expectf(t, len(pending_locks) == 0, "seed %v: %v locks could not be opened", seed, len(pending_locks))
		for cell, i in g.cells {
			if game.is_floor(cell.terrain) { testing.expectf(t, reached[i], "seed %v: floor cell %v unreachable", seed, i) }
		}
	}
}

@(test)
a_scripted_player_can_win_real_levels :: proc(t: ^testing.T) {
	// Not a clever player: walks a shortest path to the exit key, then the exit, attacking whatever stands in the
	// way and fetching a key when a lock blocks. Proves rules, generator and moves fit together on real levels.
	g := new(game.Game)
	defer free(g)
	wins, finished := 0, 0
	for seed in 0 ..< 12 {
		g.difficulty = .Easy
		testing.expect(t, game.start_game(g, u64(seed + 500)))
		for _ in 0 ..< 20_000 {
			if !game.can_continue(g) { break }
			if !step_toward(g, .Exit if g.hunter.exit_key else .Exit_Key) { break }
		}
		if game.is_winner(g) { wins += 1 }
		if game.is_winner(g) || !game.is_alive(g) { finished += 1 }
	}
	testing.expect_value(t, finished, 12)
	testing.expectf(t, wins >= 3, "only %v of 12 scripted games were won", wins)
}

// Moves one step along a shortest path (through anything, including locks and creatures) to the nearest object
// holding `target`, preferring keys when a lock blocks. Returns false if nothing is found.
step_toward :: proc(g: ^game.Game, target: game.Item_Type) -> bool {
	dist := make([]int, len(g.cells), context.temp_allocator)
	for &d in dist { d = -1 }
	first := make([]game.Direction, len(g.cells), context.temp_allocator)
	queue := make([dynamic]int, context.temp_allocator)
	start := game.room_index(g.hunter.column, g.hunter.row)
	dist[start] = 0
	append(&queue, start)
	want_key := g.hunter.keys == 0
	for head := 0; head < len(queue); head += 1 {
		i := queue[head]
		cell := g.cells[i]
		o := cell.object
		hit := (o.kind == .Item && o.item == target) || (o.kind == .Creature && o.has_drop && o.item == target)
		if i != start && hit {
			// walk back? we stored the first direction for each cell
			game.move_hunter(g, first[i])
			return true
		}
		for d in game.Direction {
			dc, dr := game.direction_delta(d)
			column, row := i % game.ROOM_COLUMNS + dc, i / game.ROOM_COLUMNS + dr
			if !game.room_in_bounds(column, row) { continue }
			n := game.room_index(column, row)
			if dist[n] >= 0 || !game.is_floor(g.cells[n].terrain) { continue }
			no := g.cells[n].object
			is_lock := no.kind == .Item && (no.item == .Door_NS || no.item == .Door_EW)
			if is_lock && want_key { continue } // without a key a lock is a wall
			dist[n] = dist[i] + 1
			first[n] = first[i] if i != start else d
			append(&queue, n)
		}
	}
	// nothing reachable: fetch a key if any lies outside
	if target != .Key { return step_toward(g, .Key) }
	return false
}
