#pragma once
#include "Room\Room.h"
#include "TerrainType.h"
#include "CreatureType.h"
class GameData
{
private:
	Room<TerrainType, CreatureType> room;
	Creature<TerrainType, CreatureType>* hunter;
	void ClearRoom();
	void ClearHunter();
	void ScaffoldMaze();
	void SmootheTerrain();
	void GenerateRoom();
	void FlagifyCell(int, int);
public:
	GameData();
	~GameData();
	const Room<TerrainType, CreatureType>& GetRoom() const;
	Room<TerrainType, CreatureType>& GetRoom();
	const Creature<TerrainType, CreatureType>* GetHunter() const;
	Creature<TerrainType, CreatureType>* GetHunter();
	void UpdateRoom();
	void Start();
};
