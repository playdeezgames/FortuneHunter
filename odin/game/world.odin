package game

// The level and what stands in it. Plain values, no pointers: a cell holds at most one object, and a creature that
// stands on an item remembers it as its drop (the original's Creature::drop).

ROOM_COLUMNS :: MAZE_COLUMNS * 2 + 1
ROOM_ROWS :: MAZE_ROWS * 2 + 1

Cell_Flag :: enum u8 { Explored, Lit }

Object_Kind :: enum u8 { None, Hunter, Item, Creature }

Object :: struct {
	kind:     Object_Kind,
	item:     Item_Type,     // Item: what it is. Creature: the drop's type when has_drop
	creature: Creature_Type, // Creature only
	has_drop: bool,          // Creature only
	wounds:   int,           // Creature only
}

Cell :: struct {
	terrain: Terrain_Type,
	flags:   bit_set[Cell_Flag],
	object:  Object,
}

is_floor :: proc "contextless" (t: Terrain_Type) -> bool { return t == .Floor || t == .Floor_Dead_End }

room_index :: proc "contextless" (column, row: int) -> int { return column + row * ROOM_COLUMNS }

room_in_bounds :: proc "contextless" (column, row: int) -> bool {
	return column >= 0 && column < ROOM_COLUMNS && row >= 0 && row < ROOM_ROWS
}

// The sprite type of an object (what the renderer draws).
object_type_of :: proc(o: Object) -> Object_Type {
	items := ITEM_DESCRIPTORS
	creatures := CREATURE_DESCRIPTORS
	switch o.kind {
	case .Item:     return items[o.item].object_type
	case .Creature: return creatures[o.creature].object_type
	case .Hunter, .None: return .Hunter
	}
	return .Hunter
}

// 1 to 10 for a creature's health bar, 0 when nothing is left (Creature::GetHealthLevel).
creature_health_level :: proc(o: Object) -> int {
	creatures := CREATURE_DESCRIPTORS
	health := creatures[o.creature].health
	left := max(health - o.wounds, 0)
	return left * 10 / health
}
