package game

// Sound effects of config/sfx.json. The core only says which effect to play; the platform plays it.

Sound_Id :: enum u8 {
	None,
	Ting, Unlock, Get_Key, Exit_Key, Exit, Door_Locked, Bump_Wall, Get_Shield, Get_Potion, Hit_Zombie,
	Dead_Zombie, Hit_Hunter, Dead_Hunter, Woo_Hoo, Trap, Badoosh, Shucks,
}

// JSON key and file (relative to the asset root) of each effect; None has no file.
SOUND_FILES :: [Sound_Id]struct { name, file: string } {
	.None         = {"", ""},
	.Ting         = {"ting", "assets/audio/sfx/ting.wav"},
	.Unlock       = {"unlock", "assets/audio/sfx/unlock.wav"},
	.Get_Key      = {"getkey", "assets/audio/sfx/getkey.wav"},
	.Exit_Key     = {"exitkey", "assets/audio/sfx/exitkey.wav"},
	.Exit         = {"exit", "assets/audio/sfx/exit.wav"},
	.Door_Locked  = {"doorlocked", "assets/audio/sfx/doorlocked.wav"},
	.Bump_Wall    = {"bumpwall", "assets/audio/sfx/bumpwall.wav"},
	.Get_Shield   = {"getshield", "assets/audio/sfx/getshield.wav"},
	.Get_Potion   = {"getpotion", "assets/audio/sfx/getpotion.wav"},
	.Hit_Zombie   = {"hitzombie", "assets/audio/sfx/hitzombie.wav"},
	.Dead_Zombie  = {"deadzombie", "assets/audio/sfx/deadzombie.wav"},
	.Hit_Hunter   = {"hithunter", "assets/audio/sfx/hithunter.wav"},
	.Dead_Hunter  = {"deadhunter", "assets/audio/sfx/deadhunter.wav"},
	.Woo_Hoo      = {"woohoo", "assets/audio/sfx/woohoo.wav"},
	.Trap         = {"trap", "assets/audio/sfx/trap.wav"},
	.Badoosh      = {"badoosh", "assets/audio/sfx/badoosh.wav"},
	.Shucks       = {"shucks", "assets/audio/sfx/shucks.wav"},
}
