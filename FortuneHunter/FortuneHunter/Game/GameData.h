#pragma once
#include "Room.h"
class GameData
{
private:
	Room room;
public:
	GameData();
	const Room& GetRoom() const;
	Room& GetRoom();
};
