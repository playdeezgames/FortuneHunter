package game

// The ROM font: a white-on-transparent 256 by 256 sheet of 16 by 16 cells, one per character code (the cell of code c
// is column c mod 16, row c div 16; config/romfont.json maps codes 32 to 127 that way and a test checks it). Every
// glyph advances 16 pixels. Text is tinted to a palette colour; the C++ menus draw a black copy 4 pixels down and
// right first as a drop shadow.

GLYPH_SIZE :: 16
GLYPH_FIRST :: 32
GLYPH_LAST :: 127
DROP_SHADOW_X :: 4
DROP_SHADOW_Y :: 4

has_glyph :: proc "contextless" (c: u8) -> bool { return c >= GLYPH_FIRST && c <= GLYPH_LAST }

// Width in pixels of the characters that have a glyph (the rest are skipped, as in the original).
text_width :: proc(text: string) -> int {
	n := 0
	for i in 0 ..< len(text) { if has_glyph(text[i]) { n += GLYPH_SIZE } }
	return n
}

// Draws `text` with its top left at (x, y); returns the x after the last glyph.
draw_text :: proc(core: ^Core, canvas: ^Canvas, x, y: int, text: string, color: Color) -> int {
	tint := color_pixel(color)
	x := x
	for i in 0 ..< len(text) {
		c := text[i]
		if !has_glyph(c) { continue }
		draw_region(canvas, core.images[.Font], int(c) % 16 * GLYPH_SIZE, int(c) / 16 * GLYPH_SIZE, GLYPH_SIZE, GLYPH_SIZE, x, y, tint)
		x += GLYPH_SIZE
	}
	return x
}

// Centred on x (the original's WriteTextCentered: x - width / 2, integer division).
draw_text_centered :: proc(core: ^Core, canvas: ^Canvas, x, y: int, text: string, color: Color) {
	draw_text(core, canvas, x - text_width(text) / 2, y, text, color)
}

// Text with the menus' drop shadow: a black copy offset by (4, 4) underneath.
draw_text_shadowed :: proc(core: ^Core, canvas: ^Canvas, x, y: int, text: string, color: Color, centered := false) {
	if centered {
		draw_text_centered(core, canvas, x + DROP_SHADOW_X, y + DROP_SHADOW_Y, text, .Black)
		draw_text_centered(core, canvas, x, y, text, color)
	} else {
		draw_text(core, canvas, x + DROP_SHADOW_X, y + DROP_SHADOW_Y, text, .Black)
		draw_text(core, canvas, x, y, text, color)
	}
}
