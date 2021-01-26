#pragma once
#include "Room\Room.h"
#include "TerrainType.h"
#include "CreatureType.h"
#include "ItemType.h"
class GameData
{
private:
	Room<TerrainType, ItemType, CreatureType> room;
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
	const Room<TerrainType, ItemType, CreatureType>& GetRoom() const;
	Room<TerrainType, ItemType, CreatureType>& GetRoom();
	const Creature<TerrainType, CreatureType>* GetHunter() const;
	Creature<TerrainType, CreatureType>* GetHunter();
	void UpdateRoom();
	void Start();
};
