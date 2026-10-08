package game

// The About screen's QR code (qr_data.odin is generated from the link by tools/gen/gen_qr.py): dark modules on a white
// square with the four-module quiet zone scanners need. Centred on `center_x`, top edge at `top`.

QR_QUIET_ZONE :: 4

draw_qr :: proc(canvas: ^Canvas, center_x, top, scale: int) {
	rows := QR_ROWS
	side := (QR_SIZE + 2 * QR_QUIET_ZONE) * scale
	left := center_x - side / 2
	fill_rect(canvas, {left, top, side, side}, rgba(255, 255, 255))
	for y in 0 ..< QR_SIZE {
		for x in 0 ..< QR_SIZE {
			if rows[y] >> uint(x) & 1 == 1 {
				fill_rect(canvas, {left + (x + QR_QUIET_ZONE) * scale, top + (y + QR_QUIET_ZONE) * scale, scale, scale}, rgba(0, 0, 0))
			}
		}
	}
}
