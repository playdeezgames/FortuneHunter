#pragma once
#include "TerrainType.h"
#include "ObjectType.h"
#include "CreatureDescriptor.h"
#include "RoomCellFlags.h"
#include "HealthLevel.h"
#include "DescribedObject.h"
class Creature : public DescribedObject<CreatureDescriptor>
{
private:
	mutable ObjectType objectType;//this is a cache variable

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
	int GetAttackStrength() const;
};

