#pragma once
#include "BaseDescriptor.h"
#include "ItemType.h"
#include <string>
#include <vector>
#include "json.hpp"
#include "CreatureType.h"
class ItemDescriptor : public BaseDescriptor
{
private:
	ItemType itemType;
	std::string pickUpSfx;
	std::string failureSfx;
	bool stopsMovement;
	size_t deadEndAppearing;
	std::vector<CreatureType> protectors;
public:
	ItemDescriptor
	(
		const nlohmann::json&
	);
	ItemType GetItemType() const;
	const std::string& GetPickUpSfx() const;
	const std::string& GetFailureSfx() const;
	bool DoesStopMovement() const;
	size_t GetDeadEndAppearing() const;
	const std::vector<CreatureType> GetProtectors() const;
};

