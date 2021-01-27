#pragma once
#include "Room\Room.h"
#include "Room\RoomDirection.h"
#include "TerrainType.h"
#include "ObjectType.h"
#include "Maze\Maze.h"
class GameData
{
private:
	Room<TerrainType, ObjectType> room;
	RoomCellObject<TerrainType, ObjectType>* hunter;
	void ClearRoom();
	void ClearHunter();
	void ScaffoldMazeCell(int, int, const MazeCell*);
	void ScaffoldMazeCells(const Maze&);
	void ScaffoldMaze();
	void SmootheTerrain();
	void GenerateRoom();
	int FlagifyDirection(int, int, RoomDirection, int);
	void FlagifyCell(int, int);
	size_t moves;
	void IncrementMove();
	void UpdateRoom();
	const RoomCellObject<TerrainType, ObjectType>* GetHunter() const;
	RoomCellObject<TerrainType, ObjectType>* GetHunter();
	static size_t PlotColumn(size_t, size_t);
	static size_t PlotRow(size_t, size_t);
	void ClearLights();
	void LightAndExploreAroundHunter();
public:
	GameData();
	~GameData();
	const Room<TerrainType, ObjectType>& GetRoom() const;
	Room<TerrainType, ObjectType>& GetRoom();
	void Start();
	size_t GetMoves() const;
	void MoveHunter(RoomDirection);
};
