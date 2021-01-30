#pragma once
#include "RoomCellObject.h"
#include "TerrainType.h"
#include "ObjectType.h"
#include "CreatureDescriptor.h"
class Creature : public tggd::common::RoomCellObject<TerrainType, ObjectType>
{
private:
	const CreatureDescriptor* creatureDescriptor;
public:
	Creature(const CreatureDescriptor*);
	const ObjectType& GetData() const;
};

