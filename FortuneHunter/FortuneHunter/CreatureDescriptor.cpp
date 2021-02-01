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
	: BaseDescriptor(objectType, numberAppearing, spawnTerrains)
	, spawnObjects(spawnObjects)
	, health(health)
	, attackStrength(attackStrength)
{

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
