#include "BaseDescriptor.h"
const std::string PROPERTY_OBJECT_TYPE = "objectType";
const std::string PROPERTY_NUMBER_APPEARING = "numberAppearing";
const std::string PROPERTY_SPAWN_TERRAIN = "canSpawnOnTerrain";

BaseDescriptor::BaseDescriptor
(
	const nlohmann::json& properties
)
	: objectType()
	, numberAppearing(0)
	, spawnTerrains()
{
	objectType = (ObjectType)properties[PROPERTY_OBJECT_TYPE];
	numberAppearing = (size_t)properties[PROPERTY_NUMBER_APPEARING];
	auto& terrains = properties[PROPERTY_SPAWN_TERRAIN];
	for (auto& terrain : terrains)
	{
		spawnTerrains.insert((TerrainType)terrain);
	}
}

ObjectType BaseDescriptor::GetObjectType() const
{
	return objectType;
}

size_t BaseDescriptor::GetNumberAppearing() const
{
	return numberAppearing;
}

bool BaseDescriptor::CanSpawnOnTerrain(TerrainType terrainType) const
{
	return spawnTerrains.contains(terrainType);
}
