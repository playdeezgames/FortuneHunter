#pragma once
#include "Room\Room.h"
#include "Room\CreatureType.h"
class GameData
{
private:
	Room<CreatureType> room;
	Creature<CreatureType>* hunter;
	void ClearRoom();
	void ClearHunter();
	void ScaffoldMaze();
	void SmootheTerrain();
	void GenerateRoom();
	void FlagifyCell(int, int);
public:
	GameData();
	~GameData();
	const Room<CreatureType>& GetRoom() const;
	Room<CreatureType>& GetRoom();
	const Creature<CreatureType>* GetHunter() const;
	Creature<CreatureType>* GetHunter();
	void Start();
};
