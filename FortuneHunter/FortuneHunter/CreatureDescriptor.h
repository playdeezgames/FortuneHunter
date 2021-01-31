#pragma once
#include "ObjectType.h"
#include "TerrainType.h"
#include <set>
class CreatureDescriptor
{
private:
	ObjectType objectType;
	size_t numberAppearing;
	std::set<TerrainType> spawnTerrains;
	std::set<ObjectType> spawnObjects;
	int health;
	int attackStrength;
public:
	CreatureDescriptor(ObjectType, size_t, const std::set<TerrainType>&, const std::set<ObjectType>&, int, int);
	ObjectType GetObjectType() const;
	size_t GetNumberAppearing() const;
	bool CanSpawnOnTerrain(TerrainType) const;
	bool CanSpawnOnObject(ObjectType) const;
	int GetHealth() const;
	int GetAttackStrength() const;
};