#include "CreatureDescriptorManager.h"
#include "json.hpp"
#include "Utility.h"
CreatureDescriptorManager::CreatureDescriptorManager()
	: creatureDescriptors()
{

}

const std::string PROPERTY_OBJECT_TYPE = "objectType";
const std::string PROPERTY_NUMBER_APPEARING = "numberAppearing";
const std::string PROPERTY_SPAWN_TERRAIN = "canSpawnOnTerrain";
const std::string PROPERTY_SPAWN_OBJECT = "canSpawnOnObject";

void CreatureDescriptorManager::Start(const std::string& fileName)
{
	nlohmann::json j = tggd::common::Utility::LoadJSON(fileName);
	for (auto& item : j.items())
	{
		CreatureType creatureType = (CreatureType)tggd::common::Utility::StringToInt(item.key());
		auto& properties = item.value();
		ObjectType objectType = (ObjectType)properties[PROPERTY_OBJECT_TYPE];
		size_t numberAppearing = (size_t)properties[PROPERTY_NUMBER_APPEARING];
		std::set<TerrainType> spawnTerrains;
		auto& terrains = properties[PROPERTY_SPAWN_TERRAIN];
		for (auto& terrain : terrains)
		{
			spawnTerrains.insert((TerrainType)terrain);
		}
		std::set<ObjectType> spawnObjects;
		auto& objects = properties[PROPERTY_SPAWN_OBJECT];
		for (auto& object : objects)
		{
			spawnObjects.insert((ObjectType)object);
		}
		creatureDescriptors[creatureType] = new CreatureDescriptor(objectType, numberAppearing, spawnTerrains, spawnObjects);
	}
}

void CreatureDescriptorManager::Finish()
{
	for (auto& entry : creatureDescriptors)
	{
		if (entry.second)
		{
			delete entry.second;
			entry.second = nullptr;
		}
	}
}

std::vector<CreatureType> CreatureDescriptorManager::GetCreatureTypes() const
{
	std::vector<CreatureType> result;
	for (auto& entry : creatureDescriptors)
	{
		result.push_back(entry.first);
	}
	return result;
}

const CreatureDescriptor* CreatureDescriptorManager::GetDescriptor(CreatureType creatureType) const
{
	auto iter = creatureDescriptors.find(creatureType);
	if (iter != creatureDescriptors.end())
	{
		return iter->second;
	}
	return nullptr;
}
