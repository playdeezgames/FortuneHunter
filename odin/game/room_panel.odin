package game

// The room panel (RoomPanelRenderer.cpp): the 31 by 31 cell level drawn with 16 pixel tiles, each cell offset by half
// a tile so the hunter's surroundings centre on the tile grid, clipped to the left 480 by 480 pixels. Cells never
// explored are left alone (the background picture shows its own "unexplored" pattern); explored cells are drawn
// as terrain, object and health bar, and covered by the dither tile unless they are lit now.

ROOM_PANEL_CLIP :: Rect{0, 0, 480, 480}
CELL_SIZE :: 16

draw_room_panel :: proc(core: ^Core, canvas: ^Canvas, g: ^Game) {
	terrain_sprites := TERRAIN_SPRITES
	object_sprites := OBJECT_SPRITES
	health_bars := HEALTH_BAR_SPRITES
	set_clip(canvas, ROOM_PANEL_CLIP)
	for column in 0 ..< ROOM_COLUMNS {
		for row in 0 ..< ROOM_ROWS {
			cell := g.cells[room_index(column, row)]
			if !(.Explored in cell.flags) { continue }
			x := column * CELL_SIZE - CELL_SIZE / 2
			y := row * CELL_SIZE - CELL_SIZE / 2
			draw_sprite(core, canvas, terrain_sprites[cell.terrain], x, y)
			if cell.object.kind != .None {
				draw_sprite(core, canvas, object_sprites[object_type_of(cell.object)], x, y)
				if cell.object.kind == .Creature && .Lit in cell.flags {
					if level := creature_health_level(cell.object); level > 0 { draw_sprite(core, canvas, health_bars[level], x, y) }
				}
			}
			if !(.Lit in cell.flags) { draw_sprite(core, canvas, .Dither, x, y) }
		}
	}
	clear_clip(canvas)
}
