#include "CreatureDescriptor.h"
const std::string PROPERTY_SPAWN_OBJECT = "canSpawnOnObject";
const std::string PROPERTY_HEALTH = "health";
const std::string PROPERTY_ATTACK_STRENGTH = "attackStrength";

CreatureDescriptor::CreatureDescriptor
(
	const nlohmann::json& properties
)
	: BaseDescriptor(properties)
	, spawnObjects()
	, health(0)
	, attackStrength(0)
{
	auto& objects = properties[PROPERTY_SPAWN_OBJECT];
	for (auto& object : objects)
	{
		spawnObjects.insert((ObjectType)object);
	}
	health = properties[PROPERTY_HEALTH];
	attackStrength = properties[PROPERTY_ATTACK_STRENGTH];
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
