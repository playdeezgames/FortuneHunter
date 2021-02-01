#include "ItemDescriptorManager.h"
#include "Utility.h"
ItemType ItemDescriptorManager::ParseKey(const std::string& key)
{
	return (ItemType)tggd::common::Utility::StringToInt(key);
}

const std::string PROPERTY_OBJECT_TYPE = "objectType";
const std::string PROPERTY_NUMBER_APPEARING = "numberAppearing";
const std::string PROPERTY_SPAWN_TERRAIN = "canSpawnOnTerrain";

ItemDescriptor* ItemDescriptorManager::ParseDescriptor(const nlohmann::json& properties)
{
	ObjectType objectType = (ObjectType)properties[PROPERTY_OBJECT_TYPE];
	size_t numberAppearing = (size_t)properties[PROPERTY_NUMBER_APPEARING];
	std::set<TerrainType> spawnTerrains;
	auto& terrains = properties[PROPERTY_SPAWN_TERRAIN];
	for (auto& terrain : terrains)
	{
		spawnTerrains.insert((TerrainType)terrain);
	}
	return new ItemDescriptor(objectType, numberAppearing, spawnTerrains);
}
