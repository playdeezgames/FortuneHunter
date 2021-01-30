#include "Creature.h"
#include "Utility.h"
Creature::Creature
(
	const CreatureDescriptor* creatureDescriptor,
	tggd::common::RoomCellObject<TerrainType, ObjectType>* drop
)
 : RoomCellObject<TerrainType, ObjectType>()
 , creatureDescriptor(creatureDescriptor)
 , drop(drop)
{

}

const ObjectType& Creature::GetData() const
{
	objectType = creatureDescriptor->GetObjectType();//mutable is a cheezy way to get rid of a warning
	return objectType;
}

tggd::common::RoomCellObject<TerrainType, ObjectType>* Creature::GetDrop() const
{
	return drop;
}

Creature::~Creature()
{
	tggd::common::Utility::SafeDelete(drop);
}

