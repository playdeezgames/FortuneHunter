#include "CreatureDescriptor.h"
const std::string PROPERTY_SPAWN_OBJECT = "canSpawnOnObject";
const std::string PROPERTY_HEALTH = "health";
const std::string PROPERTY_ATTACK_STRENGTH = "attackStrength";
const std::string PROPERTY_DAMAGE_SFX = "damageSfx";
const std::string PROPERTY_DEATH_SFX = "deathSfx";

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
	deathSfx = properties[PROPERTY_DEATH_SFX];
	damageSfx = properties[PROPERTY_DAMAGE_SFX];
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

const std::string CreatureDescriptor::GetDamageSfx() const
{
	return damageSfx;
}

const std::string CreatureDescriptor::GetDeathSfx() const
{
	return deathSfx;
}
