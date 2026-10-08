package game

// Builds a level (RoomGenerator.cpp): maze, loops, terrain smoothing, locks on every dead end, one key per dead end,
// the exit, exit key and upgrades in dead ends (upgrades guarded by minibosses), diamonds in the remaining dead
// ends, loose items, then zombies. Every random-placement loop is capped; generate_room returns false if a cap is
// hit (the caller just tries again).

MAX_PLACEMENT_TRIES :: 20_000
MAX_DEAD_ENDS :: MAZE_COLUMNS * MAZE_ROWS

Dead_Ends :: struct {
	cells: [MAX_DEAD_ENDS][2]int, // room (column, row)
	count: int,
}

// Index = north 1, east 2, south 4, west 8: which sides of a wall cell touch another wall (RoomGenerator's flagMap).
@(private)
wall_by_sides :: proc(sides: int) -> Terrain_Type {
	table := [16]Terrain_Type{
		.Floor, .Wall_N, .Wall_E, .Wall_NE, .Wall_S, .Wall_NS, .Wall_ES, .Wall_NES,
		.Wall_W, .Wall_NW, .Wall_EW, .Wall_NEW, .Wall_SW, .Wall_NSW, .Wall_ESW, .Wall_NESW,
	}
	return table[sides]
}

generate_room :: proc(cells: ^[ROOM_COLUMNS * ROOM_ROWS]Cell, rng: ^Rng) -> bool {
	dead_ends: Dead_Ends
	scaffold_maze(cells, rng, &dead_ends)
	smooth_terrain(cells)
	populate_locks(cells, &dead_ends)
	populate_keys(cells, rng, dead_ends.count) or_return
	populate_dead_ends(cells, rng, &dead_ends) or_return
	populate_loose_items(cells, rng) or_return
	populate_creatures(cells, rng) or_return
	return true
}

@(private)
scaffold_maze :: proc(cells: ^[ROOM_COLUMNS * ROOM_ROWS]Cell, rng: ^Rng, dead_ends: ^Dead_Ends) {
	for &cell, i in cells {
		column, row := i % ROOM_COLUMNS, i / ROOM_COLUMNS
		cell = {}
		cell.terrain = .Floor if column % 2 == 1 && row % 2 == 1 else .Wall_NESW
	}
	maze: Maze
	generate_maze(&maze, rng)
	loopify_maze(&maze, rng, LOOPIFICATIONS)
	for c in 0 ..< MAZE_COLUMNS {
		for r in 0 ..< MAZE_ROWS {
			rc, rr := c * 2 + 1, r * 2 + 1
			if maze_is_dead_end(&maze, c, r) {
				dead_ends.cells[dead_ends.count] = {rc, rr}
				dead_ends.count += 1
				cells[room_index(rc, rr)].terrain = .Floor_Dead_End
			}
			if maze_door_open(&maze, c, r, .East) { cells[room_index(rc + 1, rr)].terrain = .Floor }
			if maze_door_open(&maze, c, r, .South) { cells[room_index(rc, rr + 1)].terrain = .Floor }
		}
	}
}

@(private)
smooth_terrain :: proc(cells: ^[ROOM_COLUMNS * ROOM_ROWS]Cell) {
	// Every cell is judged by its neighbours' terrain before smoothing started: walls only ever become other walls
	// and floors never change, so one pass in place gives the same result.
	for column in 0 ..< ROOM_COLUMNS {
		for row in 0 ..< ROOM_ROWS {
			cell := &cells[room_index(column, row)]
			if is_floor(cell.terrain) { continue }
			sides := 0
			for d in Direction {
				dc, dr := direction_delta(d)
				nc, nr := column + dc, row + dr
				if !room_in_bounds(nc, nr) || !is_floor(cells[room_index(nc, nr)].terrain) {
					sides += 1 << uint(d) // north 1, east 2, south 4, west 8 (Direction's order)
				}
			}
			cell.terrain = wall_by_sides(sides)
		}
	}
}

@(private)
populate_locks :: proc(cells: ^[ROOM_COLUMNS * ROOM_ROWS]Cell, dead_ends: ^Dead_Ends) {
	for i in 0 ..< dead_ends.count {
		column, row := dead_ends.cells[i][0], dead_ends.cells[i][1]
		for d in Direction {
			dc, dr := direction_delta(d)
			cell := &cells[room_index(column + dc, row + dr)]
			if is_floor(cell.terrain) && cell.object.kind == .None {
				// the lock is a door across the passage: leaving east or west, the door runs north to south
				cell.object = {kind = .Item, item = .Door_NS if d == .East || d == .West else .Door_EW}
				break
			}
		}
	}
}

@(private)
populate_keys :: proc(cells: ^[ROOM_COLUMNS * ROOM_ROWS]Cell, rng: ^Rng, count: int) -> bool {
	remaining := count
	for _ in 0 ..< MAX_PLACEMENT_TRIES {
		if remaining == 0 { return true }
		cell := &cells[rng_below(rng, len(cells))]
		if cell.object.kind == .None && cell.terrain == .Floor {
			cell.object = {kind = .Item, item = .Key}
			remaining -= 1
		}
	}
	return remaining == 0
}

// An item, or a creature of one of the item's protector types standing on it.
@(private)
place_item :: proc(cell: ^Cell, rng: ^Rng, item: Item_Type) {
	descriptors := ITEM_DESCRIPTORS
	protectors := descriptors[item].protectors
	if card(protectors) == 0 {
		cell.object = {kind = .Item, item = item}
		return
	}
	pick := rng_below(rng, card(protectors))
	for creature in protectors {
		if pick == 0 {
			cell.object = {kind = .Creature, creature = creature, item = item, has_drop = true}
			return
		}
		pick -= 1
	}
}

@(private)
populate_dead_ends :: proc(cells: ^[ROOM_COLUMNS * ROOM_ROWS]Cell, rng: ^Rng, dead_ends: ^Dead_Ends) -> bool {
	descriptors := ITEM_DESCRIPTORS
	place_in_dead_end :: proc(cells: ^[ROOM_COLUMNS * ROOM_ROWS]Cell, rng: ^Rng, dead_ends: ^Dead_Ends, item: Item_Type) -> bool {
		if dead_ends.count == 0 { return false }
		for _ in 0 ..< MAX_PLACEMENT_TRIES {
			index := rng_below(rng, dead_ends.count)
			xy := dead_ends.cells[index]
			cell := &cells[room_index(xy[0], xy[1])]
			if cell.object.kind != .None { continue }
			place_item(cell, rng, item)
			dead_ends.cells[index] = dead_ends.cells[dead_ends.count - 1] // order does not matter
			dead_ends.count -= 1
			return true
		}
		return false
	}
	for item in Item_Type {
		for _ in 0 ..< descriptors[item].dead_end_appearing {
			place_in_dead_end(cells, rng, dead_ends, item) or_return
		}
	}
	for dead_ends.count > 0 {
		place_in_dead_end(cells, rng, dead_ends, .Diamond) or_return
	}
	return true
}

@(private)
populate_loose_items :: proc(cells: ^[ROOM_COLUMNS * ROOM_ROWS]Cell, rng: ^Rng) -> bool {
	descriptors := ITEM_DESCRIPTORS
	for item in Item_Type {
		d := descriptors[item]
		remaining := d.number_appearing
		for _ in 0 ..< MAX_PLACEMENT_TRIES {
			if remaining == 0 { break }
			cell := &cells[rng_below(rng, len(cells))]
			if cell.object.kind != .None || !(cell.terrain in d.spawn_terrains) { continue }
			place_item(cell, rng, item)
			remaining -= 1
		}
		if remaining > 0 { return false }
	}
	return true
}

@(private)
populate_creatures :: proc(cells: ^[ROOM_COLUMNS * ROOM_ROWS]Cell, rng: ^Rng) -> bool {
	descriptors := CREATURE_DESCRIPTORS
	for creature in Creature_Type {
		d := descriptors[creature]
		remaining := d.number_appearing
		for _ in 0 ..< MAX_PLACEMENT_TRIES {
			if remaining == 0 { break }
			cell := &cells[rng_below(rng, len(cells))]
			if !(cell.terrain in d.spawn_terrains) { continue }
			if cell.object.kind != .None && !(object_type_of(cell.object) in d.spawn_objects) { continue }
			// the object (an item: only items are allowed) becomes the creature's drop
			drop := cell.object
			cell.object = {kind = .Creature, creature = creature, item = drop.item, has_drop = drop.kind == .Item}
			remaining -= 1
		}
		if remaining > 0 { return false }
	}
	return true
}
