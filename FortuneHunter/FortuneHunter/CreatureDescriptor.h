#pragma once
#include "BaseDescriptor.h"
class CreatureDescriptor : public BaseDescriptor
{
private:
	std::set<ObjectType> spawnObjects;
	int health;
	int attackStrength;
public:
	CreatureDescriptor(ObjectType, size_t, const std::set<TerrainType>&, const std::set<ObjectType>&, int, int);
	bool CanSpawnOnObject(ObjectType) const;
	int GetHealth() const;
	int GetAttackStrength() const;
};