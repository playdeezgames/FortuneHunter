#pragma once
#include "..\Common\Room\RoomCellObject.h"
#include "Room\Terrain\TerrainType.h"
#include "ObjectType.h"
class SimpleObject : public tggd::common::RoomCellObject<TerrainType, ObjectType>
{
private:
	ObjectType objectType;
public:
	SimpleObject(ObjectType);
	const ObjectType& GetData() const;
};
