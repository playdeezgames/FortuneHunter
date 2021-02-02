#include "ItemDescriptor.h"
ItemDescriptor::ItemDescriptor
(
	ItemType itemType,
	ObjectType objectType, 
	size_t numberAppearing, 
	const std::set<TerrainType>& spawnTerrains
)
	: BaseDescriptor(objectType, numberAppearing, spawnTerrains)
	, itemType(itemType)
{

}

ItemType ItemDescriptor::GetItemType() const
{
	return itemType;
}
