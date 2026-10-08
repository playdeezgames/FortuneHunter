package game

// The maze (Maze.cpp): a 15 by 15 grid of cells with a door between each pair of neighbours. `Maze` stores which
// doors are open. generate_maze makes a perfect maze (randomised Prim: pick a random cell on the frontier, open a
// door to a random neighbour already inside); loopify then opens extra doors so there are loops.

MAZE_COLUMNS :: 15
MAZE_ROWS :: 15
LOOPIFICATIONS :: 48

Direction :: enum u8 { North, East, South, West }

direction_delta :: proc "contextless" (d: Direction) -> (dc, dr: int) {
	switch d {
	case .North: return 0, -1
	case .East:  return 1, 0
	case .South: return 0, 1
	case .West:  return -1, 0
	}
	return 0, 0
}

Maze :: struct {
	open_east:  [MAZE_COLUMNS * MAZE_ROWS]bool, // the door between (c, r) and (c + 1, r)
	open_south: [MAZE_COLUMNS * MAZE_ROWS]bool, // the door between (c, r) and (c, r + 1)
}

maze_in_bounds :: proc "contextless" (c, r: int) -> bool { return c >= 0 && c < MAZE_COLUMNS && r >= 0 && r < MAZE_ROWS }

// A door exists on every side that has a neighbour.
maze_has_door :: proc "contextless" (c, r: int, d: Direction) -> bool {
	dc, dr := direction_delta(d)
	return maze_in_bounds(c, r) && maze_in_bounds(c + dc, r + dr)
}

maze_door_open :: proc "contextless" (m: ^Maze, c, r: int, d: Direction) -> bool {
	if !maze_has_door(c, r, d) { return false }
	switch d {
	case .East:  return m.open_east[c + r * MAZE_COLUMNS]
	case .South: return m.open_south[c + r * MAZE_COLUMNS]
	case .West:  return m.open_east[(c - 1) + r * MAZE_COLUMNS]
	case .North: return m.open_south[c + (r - 1) * MAZE_COLUMNS]
	}
	return false
}

maze_set_door :: proc "contextless" (m: ^Maze, c, r: int, d: Direction, open: bool) {
	if !maze_has_door(c, r, d) { return }
	switch d {
	case .East:  m.open_east[c + r * MAZE_COLUMNS] = open
	case .South: m.open_south[c + r * MAZE_COLUMNS] = open
	case .West:  m.open_east[(c - 1) + r * MAZE_COLUMNS] = open
	case .North: m.open_south[c + (r - 1) * MAZE_COLUMNS] = open
	}
}

// A cell with exactly one open door (MazeCell::IsDeadEnd).
maze_is_dead_end :: proc "contextless" (m: ^Maze, c, r: int) -> bool {
	count := 0
	for d in Direction { if maze_door_open(m, c, r, d) { count += 1 } }
	return count == 1
}

generate_maze :: proc(m: ^Maze, rng: ^Rng) {
	m^ = {}
	inside: [MAZE_COLUMNS * MAZE_ROWS]bool
	seen: [MAZE_COLUMNS * MAZE_ROWS]bool // inside or on the frontier
	frontier: [MAZE_COLUMNS * MAZE_ROWS]int
	count := 0

	add_neighbours :: proc(c, r: int, seen: ^[MAZE_COLUMNS * MAZE_ROWS]bool, frontier: ^[MAZE_COLUMNS * MAZE_ROWS]int, count: ^int) {
		for d in Direction {
			dc, dr := direction_delta(d)
			nc, nr := c + dc, r + dr
			if maze_in_bounds(nc, nr) && !seen[nc + nr * MAZE_COLUMNS] {
				seen[nc + nr * MAZE_COLUMNS] = true
				frontier[count^] = nc + nr * MAZE_COLUMNS
				count^ += 1
			}
		}
	}

	start := rng_below(rng, MAZE_COLUMNS * MAZE_ROWS)
	inside[start] = true
	seen[start] = true
	add_neighbours(start % MAZE_COLUMNS, start / MAZE_COLUMNS, &seen, &frontier, &count)
	for count > 0 {
		i := rng_below(rng, count)
		cell := frontier[i]
		frontier[i] = frontier[count - 1]
		count -= 1
		c, r := cell % MAZE_COLUMNS, cell / MAZE_COLUMNS
		candidates: [4]Direction
		n := 0
		for d in Direction {
			dc, dr := direction_delta(d)
			nc, nr := c + dc, r + dr
			if maze_in_bounds(nc, nr) && inside[nc + nr * MAZE_COLUMNS] { candidates[n] = d; n += 1 }
		}
		maze_set_door(m, c, r, candidates[rng_below(rng, n)], true)
		inside[cell] = true
		add_neighbours(c, r, &seen, &frontier, &count)
	}
}

// Opens `count` more closed doors at random so the maze has loops. Gives up after many failed picks (it cannot
// loop forever); returns the number opened.
loopify_maze :: proc(m: ^Maze, rng: ^Rng, count: int) -> int {
	opened := 0
	for _ in 0 ..< 100_000 {
		if opened >= count { break }
		c := rng_below(rng, MAZE_COLUMNS)
		r := rng_below(rng, MAZE_ROWS)
		d := Direction(rng_below(rng, 4))
		if maze_has_door(c, r, d) && !maze_door_open(m, c, r, d) {
			maze_set_door(m, c, r, d, true)
			opened += 1
		}
	}
	return opened
}
