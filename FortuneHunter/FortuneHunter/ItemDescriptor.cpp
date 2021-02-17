#include "ItemDescriptor.h"
const std::string PROPERTY_ITEM_TYPE = "itemType";
const std::string PROPERTY_DEAD_END_APPEARING = "deadEndAppearing";
const std::string PROPERTY_PICK_UP_SFX = "pickUpSfx";
const std::string PROPERTY_STOPS_MOVEMENT = "stopsMovement";
const std::string PROPERTY_FAILURE_SFX = "failureSfx";
const std::string PROPERTY_PROTECTORS = "protectors";
const std::string PROPERTY_SPAWNS_ITEMS = "spawnItems";
const std::string PROPERTY_COUNT = "count";

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
	, protectors()
	, spawnItemType()
	, spawnItemCount(0)
{
	itemType = (ItemType)properties[PROPERTY_ITEM_TYPE];
	stopsMovement = (properties.count(PROPERTY_STOPS_MOVEMENT) > 0) ? ((bool)properties[PROPERTY_STOPS_MOVEMENT]) : (false);
	deadEndAppearing = (properties.count(PROPERTY_DEAD_END_APPEARING) > 0) ? ((size_t)properties[PROPERTY_DEAD_END_APPEARING]) : (0);
	failureSfx = (properties.count(PROPERTY_FAILURE_SFX) > 0) ? (properties[PROPERTY_FAILURE_SFX]) : ("");

	if (properties.count(PROPERTY_PROTECTORS) > 0)
	{
		auto& creatureTypes = properties[PROPERTY_PROTECTORS];
		for (auto& creatureType : creatureTypes)
		{
			protectors.push_back((CreatureType)creatureType);
		}
	}
	if (properties.count(PROPERTY_SPAWNS_ITEMS))
	{
		auto spawnItems = properties[PROPERTY_SPAWNS_ITEMS];
		spawnItemType = spawnItems[PROPERTY_ITEM_TYPE];
		spawnItemCount = spawnItems[PROPERTY_COUNT];
	}
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

const std::vector<CreatureType> ItemDescriptor::GetProtectors() const
{
	return protectors;
}

bool ItemDescriptor::DoesSpawnItems() const
{
	return spawnItemCount>0;
}

ItemType ItemDescriptor::GetSpawnItemType() const
{
	return spawnItemType;
}

size_t ItemDescriptor::GetSpawnItemCount() const
{
	return spawnItemCount;
}
