package game

// The content of config/itemdescriptors.json, creaturedescriptors.json and hunterdescriptors.json as compiled-in
// tables (a test compares them with the originals). Numbers in the JSON are the enum positions below.

Item_Type :: enum u8 {
	Shield, Potion, Diamond, Exit, Exit_Key, Key, Door_NS, Door_EW,
	Health_Upgrade, Attack_Upgrade, Armor_Upgrade, Trap,
}

Creature_Type :: enum u8 { Zombie, Miniboss }

Hunter_Award :: enum u8 { Diamond, Health, Exit_Key, Exit }

Difficulty :: enum u8 { Easy, Normal, Hard }

Item_Descriptor :: struct {
	object_type:        Object_Type,
	number_appearing:   int, // loose items scattered over the level
	dead_end_appearing: int, // items placed in dead ends
	spawn_terrains:     bit_set[Terrain_Type],
	pick_up_sfx:        Sound_Id,
	failure_sfx:        Sound_Id,
	stops_movement:     bool, // picking it up leaves the hunter where he stands (locks)
	protectors:         bit_set[Creature_Type], // a creature of one of these types stands on it
	spawn_item:         Item_Type, // picking it up spawns `spawn_count` of these
	spawn_count:        int,
}

Creature_Descriptor :: struct {
	object_type:      Object_Type,
	number_appearing: int,
	spawn_terrains:   bit_set[Terrain_Type],
	spawn_objects:    bit_set[Object_Type], // objects it may stand on (they become its drop)
	health:           int,
	attack_strength:  int,
	damage_sfx:       Sound_Id,
	death_sfx:        Sound_Id,
}

LEVELS :: 4 // upgrade levels of health, attack and armor

Hunter_Descriptor :: struct {
	name:            string,
	next_difficulty: Difficulty,
	max_healths:     [LEVELS]int,
	max_attacks:     [LEVELS]int, // a hit rolls 1 to max
	max_armors:      [LEVELS]int,
	initial_bombs:   int,
	bomb_damage:     int,
	awards:          [Hunter_Award]int,
	damage_sfx:      Sound_Id,
	death_sfx:       Sound_Id,
	bomb_sfx:        Sound_Id,
	no_bomb_sfx:     Sound_Id,
}

FLOORS :: bit_set[Terrain_Type]{.Floor}
DEAD_ENDS :: bit_set[Terrain_Type]{.Floor_Dead_End}

ITEM_DESCRIPTORS :: [Item_Type]Item_Descriptor {
	.Shield   = {object_type = .Shield, number_appearing = 30, spawn_terrains = FLOORS, pick_up_sfx = .Get_Shield},
	.Potion   = {object_type = .Potion, number_appearing = 20, spawn_terrains = FLOORS, pick_up_sfx = .Get_Potion},
	.Diamond  = {object_type = .Diamond, spawn_terrains = DEAD_ENDS, pick_up_sfx = .Ting},
	.Exit     = {object_type = .Exit, dead_end_appearing = 1, spawn_terrains = DEAD_ENDS, pick_up_sfx = .Exit},
	.Exit_Key = {object_type = .Exit_Key, dead_end_appearing = 1, spawn_terrains = DEAD_ENDS, pick_up_sfx = .Exit_Key},
	.Key      = {object_type = .Key, spawn_terrains = FLOORS, pick_up_sfx = .Get_Key},
	.Door_NS  = {object_type = .Door_NS, spawn_terrains = FLOORS, pick_up_sfx = .Unlock, failure_sfx = .Door_Locked, stops_movement = true},
	.Door_EW  = {object_type = .Door_EW, spawn_terrains = FLOORS, pick_up_sfx = .Unlock, failure_sfx = .Door_Locked, stops_movement = true},
	.Health_Upgrade = {object_type = .Health_Upgrade, dead_end_appearing = 3, spawn_terrains = DEAD_ENDS, pick_up_sfx = .Woo_Hoo,
		protectors = {.Miniboss}, spawn_item = .Trap, spawn_count = 25},
	.Attack_Upgrade = {object_type = .Attack_Upgrade, dead_end_appearing = 3, spawn_terrains = DEAD_ENDS, pick_up_sfx = .Woo_Hoo,
		protectors = {.Miniboss}, spawn_item = .Trap, spawn_count = 50},
	.Armor_Upgrade = {object_type = .Armor_Upgrade, dead_end_appearing = 3, spawn_terrains = DEAD_ENDS, pick_up_sfx = .Woo_Hoo,
		protectors = {.Miniboss}, spawn_item = .Trap, spawn_count = 10},
	.Trap     = {object_type = .Trap, number_appearing = 30, spawn_terrains = FLOORS, pick_up_sfx = .Trap},
}

CREATURE_DESCRIPTORS :: [Creature_Type]Creature_Descriptor {
	.Zombie = {object_type = .Zombie, number_appearing = 100, spawn_terrains = {.Floor, .Floor_Dead_End},
		spawn_objects = {.Key, .Diamond, .Shield, .Potion, .Trap}, health = 10, attack_strength = 1,
		damage_sfx = .Hit_Zombie, death_sfx = .Dead_Zombie},
	.Miniboss = {object_type = .Miniboss, spawn_terrains = DEAD_ENDS, health = 20, attack_strength = 2,
		damage_sfx = .Hit_Zombie, death_sfx = .Dead_Zombie},
}

HUNTER_DESCRIPTORS :: [Difficulty]Hunter_Descriptor {
	.Easy = {name = "Easy Difficulty", next_difficulty = .Normal,
		max_healths = {25, 30, 35, 40}, max_attacks = {6, 8, 10, 12}, max_armors = {10, 15, 20, 25},
		initial_bombs = 5, bomb_damage = 10, awards = {.Diamond = 500, .Health = 50, .Exit_Key = 250, .Exit = 2250},
		damage_sfx = .Hit_Hunter, death_sfx = .Dead_Hunter, bomb_sfx = .Badoosh, no_bomb_sfx = .Shucks},
	.Normal = {name = "Normal Difficulty", next_difficulty = .Hard,
		max_healths = {20, 25, 30, 35}, max_attacks = {4, 6, 8, 10}, max_armors = {10, 15, 20, 25},
		initial_bombs = 3, bomb_damage = 10, awards = {.Diamond = 1000, .Health = 100, .Exit_Key = 500, .Exit = 4500},
		damage_sfx = .Hit_Hunter, death_sfx = .Dead_Hunter, bomb_sfx = .Badoosh, no_bomb_sfx = .Shucks},
	.Hard = {name = "Hard Difficulty", next_difficulty = .Easy,
		max_healths = {15, 20, 25, 30}, max_attacks = {3, 4, 5, 6}, max_armors = {10, 15, 20, 25},
		initial_bombs = 1, bomb_damage = 10, awards = {.Diamond = 2000, .Health = 200, .Exit_Key = 1000, .Exit = 9000},
		damage_sfx = .Hit_Hunter, death_sfx = .Dead_Hunter, bomb_sfx = .Badoosh, no_bomb_sfx = .Shucks},
}
