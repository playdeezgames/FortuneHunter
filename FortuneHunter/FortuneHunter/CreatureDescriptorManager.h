#pragma once
#include "CreatureDescriptor.h"
#include "CreatureType.h"
#include "BaseDescriptorManager.h"
class CreatureDescriptorManager: public BaseDescriptorManager<CreatureType, CreatureDescriptor>
{
protected:
	CreatureType ParseKey(const std::string&);
	CreatureDescriptor* ParseDescriptor(const nlohmann::json&);
};
