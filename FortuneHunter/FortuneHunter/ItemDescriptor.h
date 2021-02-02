#pragma once
#include "BaseDescriptor.h"
#include "ItemType.h"
#include <string>
class ItemDescriptor : public BaseDescriptor
{
private:
	ItemType itemType;
	std::string pickUpSfx;
public:
	ItemDescriptor(ItemType, ObjectType, size_t, const std::set<TerrainType>&, const std::string&);
	ItemType GetItemType() const;
	const std::string& GetPickUpSfx() const;
};

