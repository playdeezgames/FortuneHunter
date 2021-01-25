#pragma once
#include "Room\Room.h"
class GameData
{
private:
	Room room;
	Creature* hunter;
public:
	GameData();
	const Room& GetRoom() const;
	Room& GetRoom();
	const Creature* GetHunter() const;
	Creature* GetHunter();
};
