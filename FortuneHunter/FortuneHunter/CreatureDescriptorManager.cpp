#include "CreatureDescriptorManager.h"
#include "json.hpp"
#include "Utility.h"
CreatureDescriptorManager::CreatureDescriptorManager(tggd::common::FinishManager& finishManager)
	: BaseDescriptorManager<CreatureType, CreatureDescriptor>(finishManager)
{

}

CreatureType CreatureDescriptorManager::ParseKey(const std::string& key)
{
	return (CreatureType)tggd::common::Utility::StringToInt(key);
}

CreatureDescriptor* CreatureDescriptorManager::ParseDescriptor(const nlohmann::json& properties)
{
	return
		new CreatureDescriptor
		(
			properties
		);
}
