#pragma once
#include "Room\Room.h"
#include "Room\RoomDirection.h"
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
	void IncrementMove();
	void UpdateRoom();
	const RoomCellObject<TerrainType, ObjectType>* GetHunter() const;
	RoomCellObject<TerrainType, ObjectType>* GetHunter();
public:
	GameData();
	~GameData();
	const Room<TerrainType, ObjectType>& GetRoom() const;
	Room<TerrainType, ObjectType>& GetRoom();
	void Start();
	size_t GetMoves() const;
	void MoveHunter(RoomDirection);
};
