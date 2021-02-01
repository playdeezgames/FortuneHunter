#include "BaseDescriptor.h"
BaseDescriptor::BaseDescriptor
(
	ObjectType objectType, 
	size_t numberAppearing, 
	const std::set<TerrainType>& spawnTerrains
)
	: objectType(objectType)
	, numberAppearing(numberAppearing)
	, spawnTerrains(spawnTerrains)
{

}

ObjectType BaseDescriptor::GetObjectType() const
{
	return objectType;
}

size_t BaseDescriptor::GetNumberAppearing() const
{
	return numberAppearing;
}

bool BaseDescriptor::CanSpawnOnTerrain(TerrainType terrainType) const
{
	return spawnTerrains.contains(terrainType);
}
