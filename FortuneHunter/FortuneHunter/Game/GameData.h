#pragma once
#include "Room\Room.h"
class GameData
{
private:
	Room room;
	Creature* hunter;
	void ClearRoom();
	void ScaffoldMaze();
	void SmootheTerrain();
	void GenerateRoom();
	void FlagifyCell(int, int);
public:
	GameData();
	const Room& GetRoom() const;
	Room& GetRoom();
	const Creature* GetHunter() const;
	Creature* GetHunter();
	void Start();
};
