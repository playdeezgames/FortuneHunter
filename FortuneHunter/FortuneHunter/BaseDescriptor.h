#pragma once
#include "ObjectType.h"
#include "TerrainType.h"
#include <set>
class BaseDescriptor
{
private:
	ObjectType objectType;
	size_t numberAppearing;
	std::set<TerrainType> spawnTerrains;
public:
	BaseDescriptor(ObjectType, size_t, const std::set<TerrainType>&);
	ObjectType GetObjectType() const;
	size_t GetNumberAppearing() const;
	bool CanSpawnOnTerrain(TerrainType) const;
};

