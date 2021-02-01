#include "CreatureDescriptorManager.h"
#include "json.hpp"
#include "Utility.h"
const std::string PROPERTY_OBJECT_TYPE = "objectType";
const std::string PROPERTY_NUMBER_APPEARING = "numberAppearing";
const std::string PROPERTY_SPAWN_TERRAIN = "canSpawnOnTerrain";
const std::string PROPERTY_SPAWN_OBJECT = "canSpawnOnObject";
const std::string PROPERTY_HEALTH = "health";
const std::string PROPERTY_ATTACK_STRENGTH = "attackStrength";

CreatureType CreatureDescriptorManager::ParseKey(const std::string& key)
{
	return (CreatureType)tggd::common::Utility::StringToInt(key);
}

CreatureDescriptor* CreatureDescriptorManager::ParseDescriptor(const nlohmann::json& properties)
{
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
	int health = properties[PROPERTY_HEALTH];
	int attackStrength = properties[PROPERTY_ATTACK_STRENGTH];
	return
		new CreatureDescriptor
		(
			objectType,
			numberAppearing,
			spawnTerrains,
			spawnObjects,
			health,
			attackStrength
		);
}
