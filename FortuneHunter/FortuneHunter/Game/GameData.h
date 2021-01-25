#pragma once
#include "Room\Room.h"
class GameData
{
private:
	Room room;
	Creature* hunter;
	void ClearRoom();
	void GenerateRoom();
public:
	GameData();
	const Room& GetRoom() const;
	Room& GetRoom();
	const Creature* GetHunter() const;
	Creature* GetHunter();
	void Start();
};
