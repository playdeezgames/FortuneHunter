#include "Creature.h"
Creature::Creature(CreatureType creatureType)
	: roomCell(nullptr)
	, creatureType(creatureType)
{

}

const RoomCell* Creature::GetRoomCell() const
{
	return roomCell;
}

RoomCell* Creature::GetRoomCell()
{
	return roomCell;
}

CreatureType Creature::GetCreatureType() const
{
	return creatureType;
}
