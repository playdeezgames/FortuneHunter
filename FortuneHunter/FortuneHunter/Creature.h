#pragma once
#include "RoomCellObject.h"
#include "TerrainType.h"
#include "ObjectType.h"
#include "CreatureDescriptor.h"
#include "RoomCellFlags.h"
#include "HealthLevel.h"
class Creature : public tggd::common::RoomCellObject<TerrainType, ObjectType, RoomCellFlags>
{
private:
	mutable ObjectType objectType;//this is a cache variable
	const CreatureDescriptor* creatureDescriptor;
	tggd::common::RoomCellObject<TerrainType, ObjectType, RoomCellFlags>* drop;
	int wounds;
public:
	Creature(const CreatureDescriptor*, tggd::common::RoomCellObject<TerrainType, ObjectType, RoomCellFlags>*);
	~Creature();
	const ObjectType& GetData() const;
	tggd::common::RoomCellObject<TerrainType, ObjectType, RoomCellFlags>* GetDrop() const;
	int GetWounds() const;
	HealthLevel GetHealthLevel() const;
	void AddWounds(int);
	bool IsDead() const;
};

