#pragma once
#include "XY.h"
#include <vector>
#include "Room.h"
#include "Maze.h"
#include "TerrainType.h"
#include "ObjectType.h"
#include "RoomCellFlags.h"
#include "RoomDirection.h"
#include "CreatureDescriptor.h"
#include "CreatureDescriptorManager.h"
class RoomGenerator
{
private:
	tggd::common::Room<TerrainType, ObjectType, RoomCellFlags>& room;
	const CreatureDescriptorManager& creatureDescriptors;
	std::vector<tggd::common::XY<size_t>> deadEnds;
	const std::vector<tggd::common::XY<size_t>>& GetDeadEnds() const;
	void AddDeadEnd(const tggd::common::XY<size_t>&);
	void RemoveDeadEndAtIndex(size_t);
	void ClearRoom();
	void ScaffoldMazeCell(int, int, const MazeCell*);
	void ScaffoldMazeCells(const Maze&);
	void ScaffoldMaze();
	void SmootheTerrain();
	int FlagifyDirection(int, int, RoomDirection, int);
	void FlagifyCell(int, int);
	void PopulateLocks();
	void PopulateKeys();
	void PopulateDeadEndObject(ObjectType);
	void PopulateDeadEnds();
	void LoopifyMaze(Maze&);
	void SpawnCreature(const CreatureDescriptor*);
	void PopulateCreatures();
public:
	RoomGenerator
	(
		tggd::common::Room<TerrainType, ObjectType, RoomCellFlags>&,
		const CreatureDescriptorManager&
	);
	void GenerateRoom();
};
