#pragma once
enum class TerrainType
{
	FLOOR,
	WALL_N,
	WALL_E,
	WALL_NE,
	WALL_S,
	WALL_NS,
	WALL_ES,
	WALL_NES,
	WALL_W,
	WALL_NW,
	WALL_EW,
	WALL_NEW,
	WALL_SW,
	WALL_NSW,
	WALL_ESW,
	WALL_NESW,
	FLOOR_DEAD_END
};
class TerrainTypeHelper
{
public:
	static bool IsFloor(TerrainType);
};