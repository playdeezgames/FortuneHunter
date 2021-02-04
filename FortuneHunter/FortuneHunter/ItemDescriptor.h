#pragma once
#include "BaseDescriptor.h"
#include "ItemType.h"
#include <string>
#include "json.hpp"
class ItemDescriptor : public BaseDescriptor
{
private:
	ItemType itemType;
	std::string pickUpSfx;
	std::string failureSfx;
	bool stopsMovement;
	size_t deadEndAppearing;
public:
	ItemDescriptor
	(
		ItemType, 
		ObjectType, 
		size_t, 
		size_t,
		const std::set<TerrainType>&, 
		const std::string&, 
		const std::string&, 
		bool
	);
	ItemType GetItemType() const;
	const std::string& GetPickUpSfx() const;
	const std::string& GetFailureSfx() const;
	bool DoesStopMovement() const;
	size_t GetDeadEndAppearing() const;
};

