#pragma once
#include "CreatureDescriptor.h"
#include "CreatureType.h"
#include "BaseDescriptorManager.h"
class CreatureDescriptorManager: public tggd::common::BaseDescriptorManager<CreatureType, CreatureDescriptor>
{
protected:
	CreatureType ParseKey(const std::string&);
	CreatureDescriptor* ParseDescriptor(const nlohmann::json&);
public:
	CreatureDescriptorManager(tggd::common::FinishManager&);
};
