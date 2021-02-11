#include "HunterDescriptorManager.h"
int HunterDescriptorManager::ParseKey(const std::string& key)
{
	return tggd::common::Utility::StringToInt(key);

}

HunterDescriptor* HunterDescriptorManager::ParseDescriptor(const nlohmann::json& j)
{
	return new HunterDescriptor(j);
}

HunterDescriptorManager::HunterDescriptorManager(tggd::common::FinishManager& finishManager)
	: BaseDescriptorManager(finishManager)
{

}
