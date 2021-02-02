#pragma once
#include "RoomCellObject.h"
#include "TerrainType.h"
#include "ObjectType.h"
#include "RoomCellFlags.h"
template <typename TDescriptor>
class DescribedObject : public tggd::common::RoomCellObject<TerrainType, ObjectType, RoomCellFlags>
{
protected:
	const TDescriptor* descriptor;
public:
	DescribedObject(const TDescriptor* descriptor) : descriptor(descriptor) {}
	const TDescriptor* GetDescriptor() const { return descriptor; }
};

