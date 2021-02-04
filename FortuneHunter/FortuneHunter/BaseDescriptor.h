#pragma once
#include "ObjectType.h"
#include "TerrainType.h"
#include <set>
#include "json.hpp"
class BaseDescriptor
{
private:
	ObjectType objectType;
	size_t numberAppearing;
	std::set<TerrainType> spawnTerrains;
public:
	BaseDescriptor(const nlohmann::json&);
	ObjectType GetObjectType() const;
	size_t GetNumberAppearing() const;
	bool CanSpawnOnTerrain(TerrainType) const;
};

