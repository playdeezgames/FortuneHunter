package game

// Decoded pixel data. The platform decodes the PNG files (the page uses a canvas, tests use core:image/png) and hands
// the core RGBA pixels; the core does not know about file formats.

// The images the game needs. IMAGE_FILES is the single source of truth for their paths (relative to the asset root);
// the page reads it through the platform_image_* exports, tests read it directly.
Image_Id :: enum u8 {
	Font,
	Tiles,
	Bg_Main_Menu,
	Bg_Instructions,
	Bg_About,
	Bg_Options,
	Bg_Confirm_Quit,
	Bg_In_Play,
	Bg_Final_Score,
	Bg_Statistics,
}

IMAGE_FILES :: [Image_Id]string {
	.Font            = "assets/images/font.png",
	.Tiles           = "assets/images/tiles.png",
	.Bg_Main_Menu    = "assets/images/backgrounds/mainmenu.png",
	.Bg_Instructions = "assets/images/backgrounds/instructions.png",
	.Bg_About        = "assets/images/backgrounds/about.png",
	.Bg_Options      = "assets/images/backgrounds/options.png",
	.Bg_Confirm_Quit = "assets/images/backgrounds/confirmquit.png",
	.Bg_In_Play      = "assets/images/backgrounds/inplay.png",
	.Bg_Final_Score  = "assets/images/backgrounds/finalscore.png",
	.Bg_Statistics   = "assets/images/backgrounds/statistics.png",
}

// RGBA pixels, bytes in memory order R,G,B,A (u32 0xAABBGGRR). Empty until the platform supplies it.
Image :: struct {
	width, height: int,
	pixels:        []u32,
}

// Gives the core an image. The core takes ownership of `pixels` (width * height values). False if the size is wrong.
set_image :: proc(core: ^Core, id: Image_Id, width, height: int, pixels: []u32) -> bool {
	if width <= 0 || height <= 0 || len(pixels) != width * height { return false }
	core.images[id] = Image{width, height, pixels}
	return true
}

all_images_loaded :: proc(core: ^Core) -> bool {
	for image in core.images {
		if image.width == 0 { return false }
	}
	return true
}
