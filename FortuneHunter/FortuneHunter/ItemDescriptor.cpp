#include "ItemDescriptor.h"
ItemDescriptor::ItemDescriptor
(
	ItemType itemType,
	ObjectType objectType, 
	size_t numberAppearing, 
	const std::set<TerrainType>& spawnTerrains,
	const std::string& pickUpSfx,
	const std::string& failureSfx,
	bool stopsMovement
)
	: BaseDescriptor(objectType, numberAppearing, spawnTerrains)
	, itemType(itemType)
	, pickUpSfx(pickUpSfx)
	, failureSfx(failureSfx)
	, stopsMovement(stopsMovement)
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

bool ItemDescriptor::DoesStopMovement() const
{
	return stopsMovement;
}

const std::string& ItemDescriptor::GetFailureSfx() const
{
	return failureSfx;
}
