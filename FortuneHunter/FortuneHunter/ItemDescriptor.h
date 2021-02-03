#pragma once
#include "BaseDescriptor.h"
#include "ItemType.h"
#include <string>
class ItemDescriptor : public BaseDescriptor
{
private:
	ItemType itemType;
	std::string pickUpSfx;
	bool stopsMovement;
public:
	ItemDescriptor(ItemType, ObjectType, size_t, const std::set<TerrainType>&, const std::string&, bool);
	ItemType GetItemType() const;
	const std::string& GetPickUpSfx() const;
	bool DoesStopMovement() const;
};

