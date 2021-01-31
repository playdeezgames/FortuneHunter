#include "Creature.h"
#include "Utility.h"
Creature::Creature
(
	const CreatureDescriptor* creatureDescriptor,
	tggd::common::RoomCellObject<TerrainType, ObjectType, RoomCellFlags>* drop
)
 : RoomCellObject<TerrainType, ObjectType, RoomCellFlags>()
 , creatureDescriptor(creatureDescriptor)
 , drop(drop)
{

}

const ObjectType& Creature::GetData() const
{
	objectType = creatureDescriptor->GetObjectType();//mutable is a cheezy way to get rid of a warning
	return objectType;
}

tggd::common::RoomCellObject<TerrainType, ObjectType, RoomCellFlags>* Creature::GetDrop() const
{
	return drop;
}

Creature::~Creature()
{
	tggd::common::Utility::SafeDelete(drop);
}

int Creature::GetWounds() const
{
	return wounds;
}

HealthLevel Creature::GetHealthLevel() const
{
	int healthLeft = creatureDescriptor->GetHealth() - GetWounds();
	return (HealthLevel)(healthLeft * (int)(HealthLevel::TEN) / creatureDescriptor->GetHealth());
}


