#pragma once
#include "BaseDescriptor.h"
#include "ItemType.h"
class ItemDescriptor : public BaseDescriptor
{
private:
	ItemType itemType;
public:
	ItemDescriptor(ItemType, ObjectType, size_t, const std::set<TerrainType>&);
	ItemType GetItemType() const;
};

