#include "CreatureDescriptorManager.h"
#include "..\json.hpp"
#include "..\Common\Utility.h"
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
		ObjectType objectType = (ObjectType)tggd::common::Utility::StringToInt(properties[PROPERTY_OBJECT_TYPE]);
		size_t numberAppearing = (size_t)tggd::common::Utility::StringToInt(properties[PROPERTY_NUMBER_APPEARING]);
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
