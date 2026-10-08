package game

// Software rasterizer. Everything draws into the core's 640 by 480 frame of u32 pixels (0xAABBGGRR; the frame is
// always opaque). Blending and tinting follow SDL's textures as the C++ game used them: a source pixel with alpha a
// replaces dst*(255-a)/255 + src*a/255, and a tint multiplies the source colour by tint/255 first.

Frame :: [FRAME_WIDTH * FRAME_HEIGHT]u32

Rect :: struct { x, y, w, h: int }

// A frame plus a clip rectangle (SDL_RenderSetClipRect in the original; the room panel clips to its 480 by 480 area).
Canvas :: struct {
	pixels: ^Frame,
	clip:   Rect,
}

canvas_init :: proc(canvas: ^Canvas, pixels: ^Frame) {
	canvas.pixels = pixels
	canvas.clip = {0, 0, FRAME_WIDTH, FRAME_HEIGHT}
}

// Sets the clip, itself clipped to the frame; set_clip(canvas, {}) style resets use clear_clip.
set_clip :: proc(canvas: ^Canvas, rect: Rect) {
	x0 := max(rect.x, 0)
	y0 := max(rect.y, 0)
	x1 := min(rect.x + rect.w, FRAME_WIDTH)
	y1 := min(rect.y + rect.h, FRAME_HEIGHT)
	canvas.clip = {x0, y0, max(x1 - x0, 0), max(y1 - y0, 0)}
}

clear_clip :: proc(canvas: ^Canvas) {
	canvas.clip = {0, 0, FRAME_WIDTH, FRAME_HEIGHT}
}

rgba :: proc "contextless" (r, g, b: u8) -> u32 {
	return 0xFF000000 | u32(b) << 16 | u32(g) << 8 | u32(r)
}

fill_canvas :: proc(canvas: ^Canvas, color: u32) {
	fill_rect(canvas, {0, 0, FRAME_WIDTH, FRAME_HEIGHT}, color)
}

fill_rect :: proc(canvas: ^Canvas, rect: Rect, color: u32) {
	clip := canvas.clip
	for row in max(rect.y, clip.y) ..< min(rect.y + rect.h, clip.y + clip.h) {
		for column in max(rect.x, clip.x) ..< min(rect.x + rect.w, clip.x + clip.w) {
			canvas.pixels[column + row * FRAME_WIDTH] = color | 0xFF000000
		}
	}
}

@(private)
mul255 :: #force_inline proc "contextless" (a, b: u32) -> u32 { return (a * b + 127) / 255 }

// Draws the rectangle (sx, sy, w, h) of `image` with its top left at (dx, dy), clipped, alpha blended, multiplied by
// `tint` (an opaque 0xFFBBGGRR colour; white leaves the image alone).
draw_region :: proc(canvas: ^Canvas, image: Image, sx, sy, w, h, dx, dy: int, tint: u32 = 0xFFFFFFFF) {
	if image.width == 0 { return }
	clip := canvas.clip
	tr, tg, tb := tint & 0xFF, tint >> 8 & 0xFF, tint >> 16 & 0xFF
	white := tint & 0xFFFFFF == 0xFFFFFF
	for row in max(0, clip.y - dy, -sy) ..< min(h, clip.y + clip.h - dy, image.height - sy) {
		y := dy + row
		for column in max(0, clip.x - dx, -sx) ..< min(w, clip.x + clip.w - dx, image.width - sx) {
			x := dx + column
			src := image.pixels[(sx + column) + (sy + row) * image.width]
			a := src >> 24
			if a == 0 { continue }
			sr, sg, sb := src & 0xFF, src >> 8 & 0xFF, src >> 16 & 0xFF
			if !white { sr, sg, sb = mul255(sr, tr), mul255(sg, tg), mul255(sb, tb) }
			if a == 255 {
				canvas.pixels[x + y * FRAME_WIDTH] = 0xFF000000 | sb << 16 | sg << 8 | sr
				continue
			}
			dst := canvas.pixels[x + y * FRAME_WIDTH]
			dr, dg, db := dst & 0xFF, dst >> 8 & 0xFF, dst >> 16 & 0xFF
			r := mul255(sr, a) + mul255(dr, 255 - a)
			g := mul255(sg, a) + mul255(dg, 255 - a)
			b := mul255(sb, a) + mul255(db, 255 - a)
			canvas.pixels[x + y * FRAME_WIDTH] = 0xFF000000 | min(b, 255) << 16 | min(g, 255) << 8 | min(r, 255)
		}
	}
}

draw_image :: proc(canvas: ^Canvas, image: Image, x, y: int) {
	draw_region(canvas, image, 0, 0, image.width, image.height, x, y)
}

draw_sprite :: proc(core: ^Core, canvas: ^Canvas, id: Sprite_Id, x, y: int, tint: u32 = 0xFFFFFFFF) {
	sprites := SPRITES
	s := sprites[id]
	draw_region(canvas, core.images[s.image], s.x, s.y, s.w, s.h, x + s.offset_x, y + s.offset_y, tint)
}
