#include "Creature.h"
Creature::Creature(const CreatureDescriptor* creatureDescriptor)
 : RoomCellObject<TerrainType, ObjectType>()
 , creatureDescriptor(creatureDescriptor)
{

}

const ObjectType& Creature::GetData() const
{
	return creatureDescriptor->GetObjectType();
}
