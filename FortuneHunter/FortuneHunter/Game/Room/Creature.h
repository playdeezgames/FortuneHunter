#pragma once
#include "CreatureType.h"
class RoomCell;
class Creature
{
private:
	friend class RoomCell;
	RoomCell* roomCell;
	CreatureType creatureType;
public:
	Creature(CreatureType);
	const RoomCell* GetRoomCell() const;
	RoomCell* GetRoomCell();
	CreatureType GetCreatureType() const;
};
