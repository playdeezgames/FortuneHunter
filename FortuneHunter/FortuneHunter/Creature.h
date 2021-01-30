#pragma once
#include "RoomCellObject.h"
#include "TerrainType.h"
#include "ObjectType.h"
#include "CreatureDescriptor.h"
class Creature : public tggd::common::RoomCellObject<TerrainType, ObjectType>
{
private:
	mutable ObjectType objectType;//this is a cache variable
	const CreatureDescriptor* creatureDescriptor;
public:
	Creature(const CreatureDescriptor*);
	const ObjectType& GetData() const;
};

