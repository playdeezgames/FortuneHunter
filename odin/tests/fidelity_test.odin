#+build !js
package tests

// While the C++ game's config files are still in the repo, check the translated Odin tables against them.

import "core:encoding/json"
import "core:fmt"
import "core:os"
import "core:testing"
import "fh:game"

read_config :: proc(t: ^testing.T, name: string) -> (root: json.Object, ok: bool) {
	path := fmt.tprint(ASSET_ROOT, "config/", name, sep = "")
	data, err := os.read_entire_file(path, context.temp_allocator)
	if err != nil { testing.expectf(t, false, "cannot read %v", path); return }
	value, jerr := json.parse_string(string(data), .JSON, true, context.temp_allocator)
	if jerr != .None { testing.expectf(t, false, "cannot parse %v: %v", path, jerr); return }
	root, ok = value.(json.Object)
	testing.expectf(t, ok, "%v is not an object", path)
	return
}

int_of :: proc(o: json.Object, key: string, fallback := 0) -> int {
	v, found := o[key]
	if !found { return fallback }
	i, is_int := v.(json.Integer)
	return int(i) if is_int else fallback
}

@(test)
sprites_match_sprites_json :: proc(t: ^testing.T) {
	root, ok := read_config(t, "sprites.json")
	if !ok { return }
	sprites := game.SPRITES
	for id in game.Sprite_Id {
		s := sprites[id]
		entry, found := root[s.name].(json.Object)
		testing.expectf(t, found, "%v: no JSON entry %v", id, s.name)
		if !found { continue }
		testing.expect_value(t, entry["texture"].(json.String), "tiles")
		testing.expectf(t, int_of(entry, "x") == s.x && int_of(entry, "y") == s.y && int_of(entry, "w") == s.w && int_of(entry, "h") == s.h, "%v: rectangle differs", id)
		testing.expectf(t, int_of(entry, "offset-x") == s.offset_x && int_of(entry, "offset-y") == s.offset_y, "%v: offset differs", id)
	}
	// every tile-sheet sprite of the JSON is in the table (backgrounds and font characters are handled elsewhere)
	tile_entries := 0
	for _, value in root {
		if o, is_obj := value.(json.Object); is_obj && o["texture"].(json.String) == "tiles" { tile_entries += 1 }
	}
	testing.expect_value(t, tile_entries, len(game.Sprite_Id))
}

@(test)
backgrounds_and_images_match_the_json :: proc(t: ^testing.T) {
	root, ok := read_config(t, "sprites.json")
	if !ok { return }
	textures, ok2 := read_config(t, "textures.json")
	if !ok2 { return }
	files := game.IMAGE_FILES
	// texture name -> path in the JSON must be exactly the set of IMAGE_FILES
	testing.expect_value(t, len(textures), len(game.Image_Id))
	for id in game.Image_Id {
		found := false
		for _, path in textures { if path.(json.String) == files[id] { found = true } }
		testing.expectf(t, found, "%v (%v) is not in textures.json", id, files[id])
	}
	// each background sprite covers its whole 640 by 480 texture
	bg_count := 0
	for _, value in root {
		o := value.(json.Object)
		texture := o["texture"].(json.String)
		if texture == "tiles" || texture == "romfont8x8" { continue }
		bg_count += 1
		testing.expect_value(t, int_of(o, "x") + int_of(o, "y"), 0)
		testing.expect_value(t, int_of(o, "w"), game.FRAME_WIDTH)
		testing.expect_value(t, int_of(o, "h"), game.FRAME_HEIGHT)
	}
	testing.expect_value(t, bg_count, 8)
}

compare_sprite_table :: proc(t: ^testing.T, file: string, keys: []int, names: []string) {
	root, ok := read_config(t, file)
	if !ok { return }
	testing.expectf(t, len(root) == len(keys), "%v has %v entries, table has %v", file, len(root), len(keys))
	for key, i in keys {
		name, found := root[fmt.tprint(key)].(json.String)
		testing.expectf(t, found && name == names[i], "%v key %v: want %v got %v", file, key, names[i], name)
	}
}

@(test)
terrain_object_and_health_tables_match_json :: proc(t: ^testing.T) {
	sprites := game.SPRITES
	terrain := game.TERRAIN_SPRITES
	keys := make([dynamic]int, context.temp_allocator)
	names := make([dynamic]string, context.temp_allocator)
	for tt in game.Terrain_Type { append(&keys, int(tt)); append(&names, sprites[terrain[tt]].name) }
	compare_sprite_table(t, "terrainSprites.json", keys[:], names[:])

	clear(&keys); clear(&names)
	objects := game.OBJECT_SPRITES
	for o in game.Object_Type { append(&keys, int(o)); append(&names, sprites[objects[o]].name) }
	compare_sprite_table(t, "objectsprites.json", keys[:], names[:])

	clear(&keys); clear(&names)
	bars := game.HEALTH_BAR_SPRITES
	for level in 1 ..= 10 { append(&keys, level); append(&names, sprites[bars[level]].name) }
	compare_sprite_table(t, "healthlevelsprites.json", keys[:], names[:])
}

@(test)
colors_match_colors_json :: proc(t: ^testing.T) {
	root, ok := read_config(t, "colors.json")
	if !ok { return }
	names := game.COLOR_NAMES
	rgb := game.COLOR_RGB
	testing.expect_value(t, len(root), len(game.Color))
	for c in game.Color {
		entry, found := root[names[c]].(json.Object)
		testing.expectf(t, found, "no colour %v", names[c])
		if !found { continue }
		testing.expectf(t, int_of(entry, "r") == int(rgb[c].r) && int_of(entry, "g") == int(rgb[c].g) && int_of(entry, "b") == int(rgb[c].b) && int_of(entry, "a") == 255, "colour %v differs", names[c])
	}
}

@(test)
romfont_maps_each_code_to_its_grid_cell :: proc(t: ^testing.T) {
	font, ok := read_config(t, "romfont.json")
	if !ok { return }
	sprites, ok2 := read_config(t, "sprites.json")
	if !ok2 { return }
	testing.expect_value(t, len(font), game.GLYPH_LAST - game.GLYPH_FIRST + 1)
	for c in game.GLYPH_FIRST ..= game.GLYPH_LAST {
		name, found := font[fmt.tprint(c)].(json.String)
		testing.expectf(t, found, "no glyph for %v", c)
		if !found { continue }
		entry := sprites[name].(json.Object)
		testing.expectf(t, int_of(entry, "x") == c % 16 * 16 && int_of(entry, "y") == c / 16 * 16 && int_of(entry, "w") == 16 && int_of(entry, "h") == 16, "glyph %v is not at its grid cell", c)
	}
}

sound_named :: proc(name: string) -> game.Sound_Id {
	files := game.SOUND_FILES
	if name == "" { return .None }
	for id in game.Sound_Id { if files[id].name == name { return id } }
	return .None
}

string_of :: proc(o: json.Object, key: string) -> string {
	s, _ := o[key].(json.String)
	return s
}

int_list :: proc(v: json.Value) -> []int {
	a, _ := v.(json.Array)
	out := make([]int, len(a), context.temp_allocator)
	for x, i in a { n, _ := x.(json.Integer); out[i] = int(n) }
	return out
}

@(test)
sounds_match_sfx_json :: proc(t: ^testing.T) {
	root, ok := read_config(t, "sfx.json")
	if !ok { return }
	files := game.SOUND_FILES
	testing.expect_value(t, len(root), len(game.Sound_Id) - 1)
	for id in game.Sound_Id {
		if id == .None { continue }
		path, found := root[files[id].name].(json.String)
		testing.expectf(t, found && path == files[id].file, "%v differs", id)
	}
}

@(test)
item_descriptors_match_json :: proc(t: ^testing.T) {
	root, ok := read_config(t, "itemdescriptors.json")
	if !ok { return }
	table := game.ITEM_DESCRIPTORS
	testing.expect_value(t, len(root), len(game.Item_Type))
	for item in game.Item_Type {
		d := table[item]
		o, found := root[fmt.tprint(int(item))].(json.Object)
		testing.expectf(t, found, "no entry for %v", item)
		if !found { continue }
		testing.expect_value(t, int_of(o, "itemType"), int(item))
		testing.expect_value(t, int_of(o, "objectType"), int(d.object_type))
		testing.expect_value(t, int_of(o, "numberAppearing"), d.number_appearing)
		testing.expect_value(t, int_of(o, "deadEndAppearing"), d.dead_end_appearing)
		terrains: bit_set[game.Terrain_Type]
		for n in int_list(o["canSpawnOnTerrain"]) { terrains += {game.Terrain_Type(n)} }
		testing.expect_value(t, terrains, d.spawn_terrains)
		testing.expect_value(t, sound_named(string_of(o, "pickUpSfx")), d.pick_up_sfx)
		testing.expect_value(t, sound_named(string_of(o, "failureSfx")), d.failure_sfx)
		stops, _ := o["stopsMovement"].(json.Boolean)
		testing.expect_value(t, stops, d.stops_movement)
		protectors: bit_set[game.Creature_Type]
		if "protectors" in o { for n in int_list(o["protectors"]) { protectors += {game.Creature_Type(n)} } }
		testing.expect_value(t, protectors, d.protectors)
		if spawn, has := o["spawnItems"].(json.Object); has {
			testing.expect_value(t, int_of(spawn, "itemType"), int(d.spawn_item))
			testing.expect_value(t, int_of(spawn, "count"), d.spawn_count)
		} else {
			testing.expect_value(t, d.spawn_count, 0)
		}
	}
}

@(test)
creature_descriptors_match_json :: proc(t: ^testing.T) {
	root, ok := read_config(t, "creaturedescriptors.json")
	if !ok { return }
	table := game.CREATURE_DESCRIPTORS
	testing.expect_value(t, len(root), len(game.Creature_Type))
	for creature in game.Creature_Type {
		d := table[creature]
		o, found := root[fmt.tprint(int(creature))].(json.Object)
		testing.expectf(t, found, "no entry for %v", creature)
		if !found { continue }
		testing.expect_value(t, int_of(o, "objectType"), int(d.object_type))
		testing.expect_value(t, int_of(o, "numberAppearing"), d.number_appearing)
		testing.expect_value(t, int_of(o, "health"), d.health)
		testing.expect_value(t, int_of(o, "attackStrength"), d.attack_strength)
		terrains: bit_set[game.Terrain_Type]
		for n in int_list(o["canSpawnOnTerrain"]) { terrains += {game.Terrain_Type(n)} }
		testing.expect_value(t, terrains, d.spawn_terrains)
		objects: bit_set[game.Object_Type]
		for n in int_list(o["canSpawnOnObject"]) { objects += {game.Object_Type(n)} }
		testing.expect_value(t, objects, d.spawn_objects)
		testing.expect_value(t, sound_named(string_of(o, "damageSfx")), d.damage_sfx)
		testing.expect_value(t, sound_named(string_of(o, "deathSfx")), d.death_sfx)
	}
}

@(test)
hunter_descriptors_match_json :: proc(t: ^testing.T) {
	root, ok := read_config(t, "hunterdescriptors.json")
	if !ok { return }
	table := game.HUNTER_DESCRIPTORS
	testing.expect_value(t, len(root), len(game.Difficulty))
	for difficulty in game.Difficulty {
		d := table[difficulty]
		o, found := root[fmt.tprint(int(difficulty))].(json.Object)
		testing.expectf(t, found, "no entry for %v", difficulty)
		if !found { continue }
		testing.expect_value(t, string_of(o, "name"), d.name)
		testing.expect_value(t, int_of(o, "nextDifficulty"), int(d.next_difficulty))
		for level in 0 ..< game.LEVELS {
			testing.expect_value(t, int_list(o["maximumHealths"])[level], d.max_healths[level])
			testing.expect_value(t, int_list(o["maximumAttacks"])[level], d.max_attacks[level])
			testing.expect_value(t, int_list(o["maximumArmors"])[level], d.max_armors[level])
		}
		testing.expect_value(t, len(int_list(o["maximumHealths"])), game.LEVELS)
		testing.expect_value(t, int_of(o, "initialBombs"), d.initial_bombs)
		testing.expect_value(t, int_of(o, "bombDamage"), d.bomb_damage)
		awards, _ := o["awards"].(json.Object)
		for award in game.Hunter_Award {
			testing.expect_value(t, int_of(awards, fmt.tprint(int(award))), d.awards[award])
		}
		testing.expect_value(t, sound_named(string_of(o, "damageSfx")), d.damage_sfx)
		testing.expect_value(t, sound_named(string_of(o, "deathSfx")), d.death_sfx)
		testing.expect_value(t, sound_named(string_of(o, "bombSfx")), d.bomb_sfx)
		testing.expect_value(t, sound_named(string_of(o, "noBombSfx")), d.no_bomb_sfx)
	}
}

@(test)
every_sound_file_exists :: proc(t: ^testing.T) {
	files := game.SOUND_FILES
	for id in game.Sound_Id {
		if id == .None { continue }
		testing.expectf(t, os.exists(fmt.tprint(ASSET_ROOT, files[id].file, sep = "")), "missing %v", files[id].file)
	}
}
