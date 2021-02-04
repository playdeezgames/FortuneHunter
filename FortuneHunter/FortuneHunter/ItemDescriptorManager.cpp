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

ItemDescriptor* ItemDescriptorManager::ParseDescriptor(const nlohmann::json& properties)
{
	return new ItemDescriptor(properties);
}
