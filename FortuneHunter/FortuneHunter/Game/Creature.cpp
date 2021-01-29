#include "Creature.h"
Creature::Creature(const CreatureDescriptor* creatureDescriptor)
 : RoomCellObject<TerrainType, ObjectType>()
 , creatureDescriptor(creatureDescriptor)
{

}

const ObjectType& Creature::GetObjectData() const
{
	return creatureDescriptor->GetObjectType();
}
