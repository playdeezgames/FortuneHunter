#+build !js
package tests

import "core:testing"
import "fh:game"

new_canvas :: proc() -> (game.Canvas, ^game.Frame) {
	frame := new(game.Frame)
	canvas: game.Canvas
	game.canvas_init(&canvas, frame)
	game.fill_canvas(&canvas, game.rgba(255, 255, 255))
	return canvas, frame
}

@(test)
draw_region_clips_to_the_frame_and_skips_transparent_pixels :: proc(t: ^testing.T) {
	canvas, frame := new_canvas()
	defer free(frame)
	game.fill_canvas(&canvas, 0)
	px := []u32{0xFF0000FF, 0x000000FF, 0xFF00FF00, 0xFFFF0000} // second pixel is transparent
	img := game.Image{2, 2, px}
	game.draw_region(&canvas, img, 0, 0, 2, 2, -1, -1) // only the last pixel is inside
	testing.expect_value(t, frame[0], u32(0xFFFF0000))
	game.draw_region(&canvas, img, 0, 0, 2, 2, game.FRAME_WIDTH - 1, game.FRAME_HEIGHT - 1) // only the first is inside
	testing.expect_value(t, frame[len(frame) - 1], u32(0xFF0000FF))
	game.draw_region(&canvas, img, 0, 0, 2, 2, 100, 100)
	testing.expect_value(t, frame[101 + 100 * game.FRAME_WIDTH], u32(0xFF000000)) // transparent pixel skipped
	testing.expect_value(t, frame[101 + 101 * game.FRAME_WIDTH], u32(0xFFFF0000))
	// a source rectangle outside the image draws nothing and does not crash
	game.draw_region(&canvas, img, 5, 5, 4, 4, 10, 10)
	game.draw_region(&canvas, img, -1, -1, 2, 2, 20, 20)
	testing.expect_value(t, frame[20 + 20 * game.FRAME_WIDTH], u32(0xFF000000))
	testing.expect_value(t, frame[21 + 21 * game.FRAME_WIDTH], u32(0xFF0000FF))
}

@(test)
half_transparent_pixels_blend_and_tint_multiplies :: proc(t: ^testing.T) {
	canvas, frame := new_canvas()
	defer free(frame)
	// 50% black over white: 255 * 127 / 255 = 127 (the dither tile of the original)
	game.draw_region(&canvas, game.Image{1, 1, []u32{0x80000000}}, 0, 0, 1, 1, 0, 0)
	testing.expect_value(t, frame[0], u32(0xFF7F7F7F))
	// a white pixel tinted dark red stays dark red; black stays black
	game.draw_region(&canvas, game.Image{2, 1, []u32{0xFFFFFFFF, 0xFF000000}}, 0, 0, 2, 1, 10, 0, game.color_pixel(.Red))
	testing.expect_value(t, frame[10], game.rgba(170, 0, 0))
	testing.expect_value(t, frame[11], game.rgba(0, 0, 0))
}

@(test)
clip_rectangle_limits_drawing :: proc(t: ^testing.T) {
	canvas, frame := new_canvas()
	defer free(frame)
	game.set_clip(&canvas, {10, 10, 5, 5})
	game.fill_rect(&canvas, {0, 0, 100, 100}, game.rgba(1, 2, 3))
	inside, outside := 0, 0
	for i in 0 ..< len(frame) {
		if frame[i] == game.rgba(1, 2, 3) { inside += 1 } else { outside += 1 }
	}
	testing.expect_value(t, inside, 25)
	testing.expect_value(t, frame[10 + 10 * game.FRAME_WIDTH], game.rgba(1, 2, 3))
	testing.expect_value(t, frame[15 + 10 * game.FRAME_WIDTH], game.rgba(255, 255, 255))
	game.clear_clip(&canvas)
	game.fill_rect(&canvas, {0, 0, 1, 1}, game.rgba(9, 9, 9))
	testing.expect_value(t, frame[0], game.rgba(9, 9, 9))
	game.set_clip(&canvas, {-50, -50, 60, 60}) // clip is itself clipped to the frame
	testing.expect_value(t, canvas.clip, game.Rect{0, 0, 10, 10})
}

@(test)
text_width_counts_only_characters_with_glyphs :: proc(t: ^testing.T) {
	testing.expect_value(t, game.text_width(""), 0)
	testing.expect_value(t, game.text_width("Hi"), 32)
	testing.expect_value(t, game.text_width("a\nb\tc"), 48) // control characters have no glyph
	testing.expect_value(t, game.text_width("é"), 0) // two UTF-8 bytes, neither in 32..127
}

@(test)
text_is_the_font_cell_tinted_and_advances_sixteen :: proc(t: ^testing.T) {
	core := new_core_with_images(t)
	defer free_core(core)
	canvas, frame := new_canvas()
	defer free(frame)
	game.fill_canvas(&canvas, 0)
	next := game.draw_text(core, &canvas, 40, 50, "A", .Red)
	testing.expect_value(t, next, 56)
	font := core.images[.Font]
	white_pixels, red_pixels, other := 0, 0, 0
	for row in 0 ..< 16 {
		for column in 0 ..< 16 {
			src := font.pixels[(int('A') % 16 * 16 + column) + (int('A') / 16 * 16 + row) * font.width]
			dst := frame[(40 + column) + (50 + row) * game.FRAME_WIDTH]
			switch src {
			case 0xFFFFFFFF: white_pixels += 1; if dst == game.rgba(170, 0, 0) { red_pixels += 1 }
			case: if src >> 24 == 0 && dst != 0xFF000000 { other += 1 }
			}
		}
	}
	testing.expect(t, white_pixels > 10, "the glyph has white pixels")
	testing.expect_value(t, red_pixels, white_pixels)
	testing.expect_value(t, other, 0) // transparent source pixels leave the frame alone
}

@(test)
centered_and_shadowed_text_use_the_originals_offsets :: proc(t: ^testing.T) {
	core := new_core_with_images(t)
	defer free_core(core)
	a, frame_a := new_canvas()
	b, frame_b := new_canvas()
	defer free(frame_a)
	defer free(frame_b)
	game.draw_text_centered(core, &a, 100, 20, "Hi", .Yellow)
	game.draw_text(core, &b, 84, 20, "Hi", .Yellow)
	testing.expect(t, frame_a^ == frame_b^, "centred text starts at x - width / 2")

	game.fill_canvas(&a, 0)
	game.fill_canvas(&b, 0)
	game.draw_text_shadowed(core, &a, 30, 30, "Hi", .White)
	game.draw_text(core, &b, 34, 34, "Hi", .Black)
	game.draw_text(core, &b, 30, 30, "Hi", .White)
	testing.expect(t, frame_a^ == frame_b^, "shadow is a black copy 4 pixels right and down, drawn first")
}

@(test)
every_sprite_lies_inside_its_image :: proc(t: ^testing.T) {
	core := new_core_with_images(t)
	defer free_core(core)
	sprites := game.SPRITES
	for id in game.Sprite_Id {
		s := sprites[id]
		image := core.images[s.image]
		testing.expectf(t, s.x >= 0 && s.y >= 0 && s.x + s.w <= image.width && s.y + s.h <= image.height, "%v is outside its image", id)
	}
}
