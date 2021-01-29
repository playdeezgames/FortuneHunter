#include "Creature.h"
Creature::Creature(const CreatureDescriptor& creatureDescriptor)
 : RoomCellObject<TerrainType, ObjectType>(creatureDescriptor.GetObjectType())
 , creatureDescriptor(creatureDescriptor)
{

}