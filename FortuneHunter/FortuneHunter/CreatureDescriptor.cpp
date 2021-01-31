#include "CreatureDescriptor.h"
CreatureDescriptor::CreatureDescriptor
(
	ObjectType objectType,
	size_t numberAppearing,
	const std::set<TerrainType>& spawnTerrains,
	const std::set<ObjectType>& spawnObjects,
	int health,
	int attackStrength
)
	: objectType(objectType)
	, numberAppearing(numberAppearing)
	, spawnTerrains(spawnTerrains)
	, spawnObjects(spawnObjects)
	, health(health)
	, attackStrength(attackStrength)
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

int CreatureDescriptor::GetHealth() const
{
	return health;
}

int CreatureDescriptor::GetAttackStrength() const
{
	return attackStrength;
}
