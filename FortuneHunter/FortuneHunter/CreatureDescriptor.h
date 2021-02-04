#pragma once
#include "BaseDescriptor.h"
class CreatureDescriptor : public BaseDescriptor
{
private:
	std::set<ObjectType> spawnObjects;
	int health;
	int attackStrength;
public:
	CreatureDescriptor(const nlohmann::json&);
	bool CanSpawnOnObject(ObjectType) const;
	int GetHealth() const;
	int GetAttackStrength() const;
};