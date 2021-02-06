#pragma once
#include "BaseDescriptor.h"
#include <string>
class CreatureDescriptor : public BaseDescriptor
{
private:
	std::set<ObjectType> spawnObjects;
	int health;
	int attackStrength;
	std::string damageSfx;
	std::string deathSfx;
public:
	CreatureDescriptor(const nlohmann::json&);
	bool CanSpawnOnObject(ObjectType) const;
	int GetHealth() const;
	int GetAttackStrength() const;
	const std::string GetDamageSfx() const;
	const std::string GetDeathSfx() const;
};