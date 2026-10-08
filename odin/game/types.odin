package game

// Terrain and object kinds and their sprites. The numbers are those of TerrainType.h / ObjectType.h, which the C++
// game's JSON refers to; the sprite tables below are translated from config/terrainSprites.json,
// config/objectsprites.json and config/healthlevelsprites.json (a test compares them with the originals).

Terrain_Type :: enum u8 {
	Floor,
	Wall_N, Wall_E, Wall_NE, Wall_S, Wall_NS, Wall_ES, Wall_NES,
	Wall_W, Wall_NW, Wall_EW, Wall_NEW, Wall_SW, Wall_NSW, Wall_ESW, Wall_NESW,
	Floor_Dead_End,
}

Object_Type :: enum u8 {
	Hunter, Key, Door_NS, Door_EW, Exit, Diamond, Zombie, Exit_Key,
	Shield, Potion, Health_Upgrade, Attack_Upgrade, Armor_Upgrade, Trap, Miniboss,
}

TERRAIN_SPRITES :: [Terrain_Type]Sprite_Id {
	.Floor = .Floor_Tile, .Wall_N = .Wall_Tile_N, .Wall_E = .Wall_Tile_E, .Wall_NE = .Wall_Tile_NE,
	.Wall_S = .Wall_Tile_S, .Wall_NS = .Wall_Tile_NS, .Wall_ES = .Wall_Tile_ES, .Wall_NES = .Wall_Tile_NES,
	.Wall_W = .Wall_Tile_W, .Wall_NW = .Wall_Tile_NW, .Wall_EW = .Wall_Tile_EW, .Wall_NEW = .Wall_Tile_NEW,
	.Wall_SW = .Wall_Tile_SW, .Wall_NSW = .Wall_Tile_NSW, .Wall_ESW = .Wall_Tile_ESW, .Wall_NESW = .Wall_Tile_NESW,
	.Floor_Dead_End = .Floor_Tile,
}

OBJECT_SPRITES :: [Object_Type]Sprite_Id {
	.Hunter = .Hunter_Creature, .Key = .Key_Item, .Door_NS = .NS_Door, .Door_EW = .EW_Door, .Exit = .Exit,
	.Diamond = .Diamond_Item, .Zombie = .Zombie_Creature, .Exit_Key = .Exit_Key_Item, .Shield = .Shield_Item,
	.Potion = .Potion_Item, .Health_Upgrade = .Health_Upgrade, .Attack_Upgrade = .Attack_Upgrade,
	.Armor_Upgrade = .Armor_Upgrade, .Trap = .Trap_Item, .Miniboss = .Miniboss_Creature,
}

// Health levels 1 to 10 (HealthLevel.h; 0 draws nothing).
HEALTH_BAR_SPRITES :: [11]Sprite_Id {
	1  = .Health_Bar_10, 2 = .Health_Bar_20, 3 = .Health_Bar_30, 4 = .Health_Bar_40, 5 = .Health_Bar_50,
	6  = .Health_Bar_60, 7 = .Health_Bar_70, 8 = .Health_Bar_80, 9 = .Health_Bar_90, 10 = .Health_Bar_100,
}
