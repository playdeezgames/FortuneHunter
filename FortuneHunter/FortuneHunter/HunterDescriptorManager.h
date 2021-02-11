#pragma once
#include "HunterDescriptor.h"
#include "BaseDescriptorManager.h"
class HunterDescriptorManager : public BaseDescriptorManager<int, HunterDescriptor>
{
protected:
	int ParseKey(const std::string&);
	HunterDescriptor* ParseDescriptor(const nlohmann::json&);
public:
	HunterDescriptorManager(tggd::common::FinishManager&);
};
