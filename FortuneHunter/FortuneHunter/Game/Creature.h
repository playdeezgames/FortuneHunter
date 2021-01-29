#pragma once
#include "Room\RoomCellObject.h"
#include "TerrainType.h"
#include "ObjectType.h"
#include "CreatureDescriptor.h"
class Creature : public RoomCellObject<TerrainType, ObjectType>
{
private:
	const CreatureDescriptor* creatureDescriptor;
public:
	Creature(const CreatureDescriptor*);
};

