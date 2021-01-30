#pragma once
#include "RoomCellObject.h"
#include "TerrainType.h"
#include "ObjectType.h"
#include "CreatureDescriptor.h"
#include "RoomCellFlags.h"
class Creature : public tggd::common::RoomCellObject<TerrainType, ObjectType, RoomCellFlags>
{
private:
	mutable ObjectType objectType;//this is a cache variable
	const CreatureDescriptor* creatureDescriptor;
	tggd::common::RoomCellObject<TerrainType, ObjectType, RoomCellFlags>* drop;
public:
	Creature(const CreatureDescriptor*, tggd::common::RoomCellObject<TerrainType, ObjectType, RoomCellFlags>*);
	~Creature();
	const ObjectType& GetData() const;
	tggd::common::RoomCellObject<TerrainType, ObjectType, RoomCellFlags>* GetDrop() const;
};

