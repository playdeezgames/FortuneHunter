#include "CreatureDescriptorManager.h"
#include "json.hpp"
#include "Utility.h"
CreatureDescriptorManager::CreatureDescriptorManager()
	: creatureDescriptors()
{

}

const std::string PROPERTY_OBJECT_TYPE = "objectType";
const std::string PROPERTY_NUMBER_APPEARING = "numberAppearing";

void CreatureDescriptorManager::Start(const std::string& fileName)
{
	nlohmann::json j = tggd::common::Utility::LoadJSON(fileName);
	for (auto& item : j.items())
	{
		CreatureType creatureType = (CreatureType)tggd::common::Utility::StringToInt(item.key());
		auto& properties = item.value();
		ObjectType objectType = (ObjectType)properties[PROPERTY_OBJECT_TYPE];
		size_t numberAppearing = (size_t)properties[PROPERTY_NUMBER_APPEARING];
		creatureDescriptors[creatureType] = new CreatureDescriptor(objectType, numberAppearing);
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
