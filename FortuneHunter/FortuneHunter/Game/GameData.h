#pragma once
#include "Room\Room.h"
#include "TerrainType.h"
#include "ObjectType.h"
class GameData
{
private:
	Room<TerrainType, ObjectType> room;
	RoomCellObject<TerrainType, ObjectType>* hunter;
	void ClearRoom();
	void ClearHunter();
	void ScaffoldMaze();
	void SmootheTerrain();
	void GenerateRoom();
	void FlagifyCell(int, int);
	size_t moves;
public:
	GameData();
	~GameData();
	const Room<TerrainType, ObjectType>& GetRoom() const;
	Room<TerrainType, ObjectType>& GetRoom();
	const RoomCellObject<TerrainType, ObjectType>* GetHunter() const;
	RoomCellObject<TerrainType, ObjectType>* GetHunter();
	void UpdateRoom();
	void Start();
	void IncrementMove();
	size_t GetMoves() const;
};
