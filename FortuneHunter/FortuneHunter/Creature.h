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
	tggd::common::RoomCellObject<TerrainType, ObjectType>* drop;
public:
	Creature(const CreatureDescriptor*, tggd::common::RoomCellObject<TerrainType, ObjectType>*);
	~Creature();
	const ObjectType& GetData() const;
	tggd::common::RoomCellObject<TerrainType, ObjectType>* GetDrop() const;
};

