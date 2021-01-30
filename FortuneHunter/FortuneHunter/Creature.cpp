#include "Creature.h"
Creature::Creature(const CreatureDescriptor* creatureDescriptor)
 : RoomCellObject<TerrainType, ObjectType>()
 , creatureDescriptor(creatureDescriptor)
{

}

const ObjectType& Creature::GetData() const
{
	objectType = creatureDescriptor->GetObjectType();//mutable is a cheezy way to get rid of a warning
	return objectType;
}
