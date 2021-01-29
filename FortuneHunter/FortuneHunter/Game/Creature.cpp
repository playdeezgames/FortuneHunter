#include "Creature.h"
Creature::Creature(const CreatureDescriptor* creatureDescriptor)
 : RoomCellObject<TerrainType, ObjectType>(creatureDescriptor->GetObjectType())//TODO: ick! possibly dereferencing a nullptr
 , creatureDescriptor(creatureDescriptor)
{

}