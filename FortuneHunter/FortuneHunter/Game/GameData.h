#pragma once
#include "Room\Room.h"
#include "TerrainType.h"
#include "ObjectType.h"
class GameData
{
private:
	Room<TerrainType, ObjectType> room;
	Creature<TerrainType, ObjectType>* hunter;
	void ClearRoom();
	void ClearHunter();
	void ScaffoldMaze();
	void SmootheTerrain();
	void GenerateRoom();
	void FlagifyCell(int, int);
public:
	GameData();
	~GameData();
	const Room<TerrainType, ObjectType>& GetRoom() const;
	Room<TerrainType, ObjectType>& GetRoom();
	const Creature<TerrainType, ObjectType>* GetHunter() const;
	Creature<TerrainType, ObjectType>* GetHunter();
	void UpdateRoom();
	void Start();
};
