#include "ItemDescriptor.h"
const std::string PROPERTY_ITEM_TYPE = "itemType";
const std::string PROPERTY_DEAD_END_APPEARING = "deadEndAppearing";
const std::string PROPERTY_PICK_UP_SFX = "pickUpSfx";
const std::string PROPERTY_STOPS_MOVEMENT = "stopsMovement";
const std::string PROPERTY_FAILURE_SFX = "failureSfx";

ItemDescriptor::ItemDescriptor
(
	const nlohmann::json& properties
)
	: BaseDescriptor(properties)
	, itemType()
	, pickUpSfx(properties[PROPERTY_PICK_UP_SFX])
	, failureSfx()
	, stopsMovement()
	, deadEndAppearing()
{
	itemType = (ItemType)properties[PROPERTY_ITEM_TYPE];
	stopsMovement = (properties.count(PROPERTY_STOPS_MOVEMENT) > 0) ? ((bool)properties[PROPERTY_STOPS_MOVEMENT]) : (false);
	deadEndAppearing = (properties.count(PROPERTY_DEAD_END_APPEARING) > 0) ? ((size_t)properties[PROPERTY_DEAD_END_APPEARING]) : (0);
	failureSfx = (properties.count(PROPERTY_FAILURE_SFX) > 0) ? (properties[PROPERTY_FAILURE_SFX]) : ("");
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

size_t ItemDescriptor::GetDeadEndAppearing() const
{
	return deadEndAppearing;
}
