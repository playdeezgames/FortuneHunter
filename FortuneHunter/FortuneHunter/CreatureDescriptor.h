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
public:
	CreatureDescriptor(ObjectType, size_t, const std::set<TerrainType>&, const std::set<ObjectType>&);
	ObjectType GetObjectType() const;
	size_t GetNumberAppearing() const;
	bool CanSpawnOnTerrain(TerrainType) const;
	bool CanSpawnOnObject(ObjectType) const;
};