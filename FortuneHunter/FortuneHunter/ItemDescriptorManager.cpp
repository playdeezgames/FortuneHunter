#include "ItemDescriptorManager.h"
#include "Utility.h"
ItemDescriptorManager::ItemDescriptorManager(tggd::common::FinishManager& finishManager)
	: BaseDescriptorManager<ItemType, ItemDescriptor>(finishManager)
{
	finishManager.Add(this);
}


ItemType ItemDescriptorManager::ParseKey(const std::string& key)
{
	return (ItemType)tggd::common::Utility::StringToInt(key);
}

const std::string PROPERTY_OBJECT_TYPE = "objectType";
const std::string PROPERTY_ITEM_TYPE = "itemType";
const std::string PROPERTY_NUMBER_APPEARING = "numberAppearing";
const std::string PROPERTY_SPAWN_TERRAIN = "canSpawnOnTerrain";

ItemDescriptor* ItemDescriptorManager::ParseDescriptor(const nlohmann::json& properties)
{
	ObjectType objectType = (ObjectType)properties[PROPERTY_OBJECT_TYPE];
	ItemType itemType = (ItemType)properties[PROPERTY_ITEM_TYPE];
	size_t numberAppearing = (size_t)properties[PROPERTY_NUMBER_APPEARING];
	std::set<TerrainType> spawnTerrains;
	auto& terrains = properties[PROPERTY_SPAWN_TERRAIN];
	for (auto& terrain : terrains)
	{
		spawnTerrains.insert((TerrainType)terrain);
	}
	return new ItemDescriptor(itemType, objectType, numberAppearing, spawnTerrains);
}
