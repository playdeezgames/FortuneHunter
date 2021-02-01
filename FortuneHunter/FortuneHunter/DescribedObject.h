#pragma once
#include "RoomCellObject.h"
template <typename TDescriptor>
class DescribedObject : public tggd::common::RoomCellObject<TerrainType, ObjectType, RoomCellFlags>
{
protected:
	const TDescriptor* descriptor;
public:
	DescribedObject(const TDescriptor* descriptor) : descriptor(descriptor) {}
};

