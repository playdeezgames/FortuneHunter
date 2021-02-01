#pragma once
#include "BaseDescriptorManager.h"
#include "ItemType.h"
#include "ItemDescriptor.h"
class ItemDescriptorManager: public BaseDescriptorManager<ItemType, ItemDescriptor>
{
protected:
	ItemType ParseKey(const std::string&);
	ItemDescriptor* ParseDescriptor(const nlohmann::json&);
};

