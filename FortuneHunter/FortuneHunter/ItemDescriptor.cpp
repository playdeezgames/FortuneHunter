#include "ItemDescriptor.h"
ItemDescriptor::ItemDescriptor
(
	ItemType itemType,
	ObjectType objectType, 
	size_t numberAppearing, 
	const std::set<TerrainType>& spawnTerrains,
	const std::string& pickUpSfx
)
	: BaseDescriptor(objectType, numberAppearing, spawnTerrains)
	, itemType(itemType)
	, pickUpSfx(pickUpSfx)
{

}

ItemType ItemDescriptor::GetItemType() const
{
	return itemType;
}

const std::string& ItemDescriptor::GetPickUpSfx() const
{
	return pickUpSfx;
}
