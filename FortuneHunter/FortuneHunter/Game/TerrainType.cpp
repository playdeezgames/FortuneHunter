#include "TerrainType.h"
bool TerrainTypeHelper::IsFloor(TerrainType terrainType)
{
	switch (terrainType)
	{
	case TerrainType::FLOOR:
	case TerrainType::FLOOR_DEAD_END:
		return true;
	default:
		return false;
	}
}