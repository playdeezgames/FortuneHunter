#include "ItemDescriptor.h"
ItemDescriptor::ItemDescriptor
(
	ObjectType objectType, 
	size_t numberAppearing, 
	const std::set<TerrainType>& spawnTerrains
)
	: BaseDescriptor(objectType, numberAppearing, spawnTerrains)
{

}
