#pragma once
#include "Room\Room.h"
#include "Room\RoomDirection.h"
#include "TerrainType.h"
#include "ObjectType.h"
#include "Maze\Maze.h"
#include "RoomGenerationContext.h"
#include "Hunter.h"
#include "..\Common\Managers\SoundManager.h"
class GameData
{
private:
	const tggd::common::SoundManager& soundManager;
	Room<TerrainType, ObjectType> room;
	Hunter* hunter;
	void ClearRoom();
	void ClearHunter();
	void ScaffoldMazeCell(int, int, const MazeCell*, RoomGenerationContext&);
	void ScaffoldMazeCells(const Maze&, RoomGenerationContext&);
	void ScaffoldMaze(RoomGenerationContext&);
	void SmootheTerrain();
	void GenerateRoom();
	int FlagifyDirection(int, int, RoomDirection, int);
	void FlagifyCell(int, int);
	size_t moves;
	void IncrementMove();
	void UpdateRoom();
	Hunter* GetHunter();
	static size_t PlotColumn(size_t, size_t);
	static size_t PlotRow(size_t, size_t);
	void ClearLights();
	void LightAndExploreAroundHunter();
	void PopulateLocks(RoomGenerationContext&);
	void PopulateKeys(RoomGenerationContext&);
	void PlaceHunter();
public:
	GameData(const tggd::common::SoundManager&);
	~GameData();
	const Hunter* GetHunter() const;
	const Room<TerrainType, ObjectType>& GetRoom() const;
	Room<TerrainType, ObjectType>& GetRoom();
	void Start();
	size_t GetMoves() const;
	void MoveHunter(RoomDirection);
};
