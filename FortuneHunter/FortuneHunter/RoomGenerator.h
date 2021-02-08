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
#include "ItemDescriptorManager.h"
class RoomGenerator
{
private:
	tggd::common::Room<TerrainType, ObjectType, RoomCellFlags>& room;
	const CreatureDescriptorManager& creatureDescriptors;
	const ItemDescriptorManager& itemDescriptors;
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
	void PopulateDeadEndItem(ItemType);
	void PopulateDeadEnds();
	void LoopifyMaze(Maze&);
	void SpawnCreature(const CreatureDescriptor*);
	void PopulateCreatures();
	void PopulateLooseItems();
	void SpawnItem(const ItemDescriptor*);
	void PlaceItem(const ItemDescriptor*, tggd::common::RoomCell<TerrainType, ObjectType, RoomCellFlags>*);
public:
	RoomGenerator
	(
		tggd::common::Room<TerrainType, ObjectType, RoomCellFlags>&,
		const CreatureDescriptorManager&,
		const ItemDescriptorManager&
	);
	void GenerateRoom();
};
