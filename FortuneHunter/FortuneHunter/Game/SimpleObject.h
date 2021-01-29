#pragma once
#include "Room\RoomCellObject.h"
#include "TerrainType.h"
#include "ObjectType.h"
class SimpleObject : public RoomCellObject<TerrainType, ObjectType>
{
private:
	ObjectType objectType;
public:
	SimpleObject(ObjectType);
	const ObjectType& GetObjectData() const;
};
