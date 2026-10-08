package game

// The 16 colours of config/colors.json (the CGA palette), used to tint the white font and to fill rectangles.
Color :: enum u8 {
	Black, Blue, Green, Cyan, Red, Magenta, Brown, Gray,
	Dark_Gray, Light_Blue, Light_Green, Light_Cyan, Light_Red, Light_Magenta, Yellow, White,
}

// Indexed by Color; JSON key names are in COLOR_NAMES (a test compares both with the original file).
COLOR_RGB :: [Color][3]u8 {
	.Black         = {0, 0, 0},
	.Blue          = {0, 0, 170},
	.Green         = {0, 170, 0},
	.Cyan          = {0, 170, 170},
	.Red           = {170, 0, 0},
	.Magenta       = {170, 0, 170},
	.Brown         = {170, 85, 0},
	.Gray          = {170, 170, 170},
	.Dark_Gray     = {85, 85, 85},
	.Light_Blue    = {85, 85, 255},
	.Light_Green   = {85, 255, 85},
	.Light_Cyan    = {85, 255, 255},
	.Light_Red     = {255, 85, 85},
	.Light_Magenta = {255, 85, 255},
	.Yellow        = {255, 255, 85},
	.White         = {255, 255, 255},
}

COLOR_NAMES :: [Color]string {
	.Black = "Black", .Blue = "Blue", .Green = "Green", .Cyan = "Cyan", .Red = "Red", .Magenta = "Magenta",
	.Brown = "Brown", .Gray = "Gray", .Dark_Gray = "DarkGray", .Light_Blue = "LightBlue", .Light_Green = "LightGreen",
	.Light_Cyan = "LightCyan", .Light_Red = "LightRed", .Light_Magenta = "LightMagenta", .Yellow = "Yellow", .White = "White",
}

color_pixel :: proc(color: Color) -> u32 {
	table := COLOR_RGB
	c := table[color]
	return rgba(c.r, c.g, c.b)
}
