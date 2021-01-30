#include "CreatureDescriptor.h"
CreatureDescriptor::CreatureDescriptor
(
	ObjectType objectType,
	size_t numberAppearing,
	const std::set<TerrainType>& spawnTerrains,
	const std::set<ObjectType>& spawnObjects
)
	: objectType(objectType)
	, numberAppearing(numberAppearing)
	, spawnTerrains(spawnTerrains)
	, spawnObjects(spawnObjects)
{

}

ObjectType CreatureDescriptor::GetObjectType() const
{
	return objectType;
}

size_t CreatureDescriptor::GetNumberAppearing() const
{
	return numberAppearing;
}

bool CreatureDescriptor::CanSpawnOnTerrain(TerrainType terrainType) const
{
	return spawnTerrains.contains(terrainType);
}

bool CreatureDescriptor::CanSpawnOnObject(ObjectType objectType) const
{
	return spawnObjects.contains(objectType);
}