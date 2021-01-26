#pragma once
#include "Room\Room.h"
#include "Terrain.h"
#include "CreatureType.h"
class GameData
{
private:
	Room<Terrain, CreatureType> room;
	Creature<Terrain, CreatureType>* hunter;
	void ClearRoom();
	void ClearHunter();
	void ScaffoldMaze();
	void SmootheTerrain();
	void GenerateRoom();
	void FlagifyCell(int, int);
public:
	GameData();
	~GameData();
	const Room<Terrain, CreatureType>& GetRoom() const;
	Room<Terrain, CreatureType>& GetRoom();
	const Creature<Terrain, CreatureType>* GetHunter() const;
	Creature<Terrain, CreatureType>* GetHunter();
	void Start();
};
