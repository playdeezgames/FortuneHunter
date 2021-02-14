#include "RoomGenerator.h"
#include "MazeConstants.h"
#include "Utility.h"
#include "SimpleObject.h"
#include "Creature.h"
#include "RoomConstants.h"
#include "Item.h"
RoomGenerator::RoomGenerator
(
	tggd::common::Room<TerrainType, ObjectType, RoomCellFlags>& room,
	const CreatureDescriptorManager& creatureDescriptors,
	const ItemDescriptorManager& itemDescriptors
)
	: deadEnds()
	, room(room)
	, creatureDescriptors(creatureDescriptors)
	, itemDescriptors(itemDescriptors)
{

}

const std::vector<tggd::common::XY<size_t>>& RoomGenerator::GetDeadEnds() const
{
	return deadEnds;
}

void RoomGenerator::AddDeadEnd(const tggd::common::XY<size_t>& xy)
{
	deadEnds.push_back(xy);
}

void RoomGenerator::RemoveDeadEndAtIndex(size_t index)
{
	deadEnds.erase(deadEnds.begin() + index);
}

static TerrainType flagMap[16] =
{
	TerrainType::FLOOR,
	TerrainType::WALL_N,
	TerrainType::WALL_E,
	TerrainType::WALL_NE,
	TerrainType::WALL_S,
	TerrainType::WALL_NS,
	TerrainType::WALL_ES,
	TerrainType::WALL_NES,
	TerrainType::WALL_W,
	TerrainType::WALL_NW,
	TerrainType::WALL_EW,
	TerrainType::WALL_NEW,
	TerrainType::WALL_SW,
	TerrainType::WALL_NSW,
	TerrainType::WALL_ESW,
	TerrainType::WALL_NESW
};
const int FLAG_NORTH = 1;
const int FLAG_EAST = 2;
const int FLAG_SOUTH = 4;
const int FLAG_WEST = 8;


static size_t PlotColumn(size_t column, size_t row)
{
	return column * 2 + 1;
}

static size_t PlotRow(size_t columne, size_t row)
{
	return row * 2 + 1;
}

void RoomGenerator::ScaffoldMazeCell(int mazeColumn, int mazeRow, const MazeCell* mazeCell)
{
	size_t roomColumn = PlotColumn(mazeColumn, mazeRow);
	size_t roomRow = PlotRow(mazeColumn, mazeRow);

	if (mazeCell->IsDeadEnd())
	{
		AddDeadEnd({ roomColumn, roomRow });
		room.GetCell(roomColumn, roomRow)->SetTerrain(TerrainType::FLOOR_DEAD_END);
	}

	if (mazeCell->HasDoor(MazeDirection::EAST) && mazeCell->GetDoor(MazeDirection::EAST)->IsOpen())
	{
		room.GetCell
		(
			RoomDirectionHelper::GetNextColumn((int)roomColumn, (int)roomRow, RoomDirection::EAST),
			RoomDirectionHelper::GetNextRow((int)roomColumn, (int)roomRow, RoomDirection::EAST)
		)->SetTerrain(TerrainType::FLOOR);
	}
	if (mazeCell->HasDoor(MazeDirection::SOUTH) && mazeCell->GetDoor(MazeDirection::SOUTH)->IsOpen())
	{
		room.GetCell
		(
			RoomDirectionHelper::GetNextColumn((int)roomColumn, (int)roomRow, RoomDirection::SOUTH),
			RoomDirectionHelper::GetNextRow((int)roomColumn, (int)roomRow, RoomDirection::SOUTH)
		)->SetTerrain(TerrainType::FLOOR);
	}
}

void RoomGenerator::ScaffoldMazeCells(const Maze& maze)
{
	for (int column = 0; column < maze.GetColumns(); ++column)
	{
		for (int row = 0; row < maze.GetRows(); ++row)
		{
			ScaffoldMazeCell(column, row, maze.GetCell(column, row));
		}
	}
}

void RoomGenerator::LoopifyMaze(Maze& maze)
{
	size_t counter = Constants::Maze::LOOPIFICATIONS;
	auto directions = MazeDirectionHelper::GetAll();
	while (counter > 0)
	{
		size_t column = (size_t)tggd::common::Utility::GenerateRandomNumberFromRange(0, (int)maze.GetColumns());
		size_t row = (size_t)tggd::common::Utility::GenerateRandomNumberFromRange(0, (int)maze.GetRows());
		MazeDirection direction = directions[tggd::common::Utility::GenerateRandomNumberFromRange(0, (int)directions.size())];
		auto mazeCell = maze.GetCell((int)column, (int)row);
		if (mazeCell->HasDoor(direction))
		{
			auto mazeDoor = mazeCell->GetDoor(direction);
			if (!mazeDoor->IsOpen())
			{
				mazeDoor->SetOpen(true);
				counter--;
			}
		}
	}
}

void RoomGenerator::ScaffoldMaze()
{
	ClearRoom();
	Maze maze(Constants::Maze::COLUMNS, Constants::Maze::ROWS);
	maze.Generate();
	LoopifyMaze(maze);
	ScaffoldMazeCells(maze);
}

int RoomGenerator::FlagifyDirection(int column, int row, RoomDirection direction, int flag)
{
	int nextColumn = RoomDirectionHelper::GetNextColumn(column, row, direction);
	int nextRow = RoomDirectionHelper::GetNextRow(column, row, direction);
	auto cell = room.GetCell(nextColumn, nextRow);
	if (!cell || !TerrainTypeHelper::IsFloor(cell->GetTerrain()))
	{
		return flag;
	}
	return 0;
}

void RoomGenerator::FlagifyCell(int column, int row)
{
	tggd::common::RoomCell<TerrainType, ObjectType, RoomCellFlags>* cell = room.GetCell(column, row);
	int flags = 0;
	if (!TerrainTypeHelper::IsFloor(cell->GetTerrain()))//TODO: a "need to be flagified" function in a helper?
	{
		flags += FlagifyDirection(column, row, RoomDirection::NORTH, FLAG_NORTH);
		flags += FlagifyDirection(column, row, RoomDirection::EAST, FLAG_EAST);
		flags += FlagifyDirection(column, row, RoomDirection::SOUTH, FLAG_SOUTH);
		flags += FlagifyDirection(column, row, RoomDirection::WEST, FLAG_WEST);
		cell->SetTerrain(flagMap[flags]);
	}
}

void RoomGenerator::SmootheTerrain()
{
	for (int column = 0; column < room.GetColumns(); ++column)
	{
		for (int row = 0; row < room.GetRows(); ++row)
		{
			FlagifyCell(column, row);
		}
	}
}

void RoomGenerator::SpawnCreature(const CreatureDescriptor* descriptor)
{
	do
	{
		int column = tggd::common::Utility::GenerateRandomNumberFromRange(0, Constants::Room::COLUMNS);
		int row = tggd::common::Utility::GenerateRandomNumberFromRange(0, Constants::Room::ROWS);
		auto cell = room.GetCell(column, row);
		auto terrainType = cell->GetTerrain();
		if (!descriptor->CanSpawnOnTerrain(terrainType))
		{
			continue;
		}
		auto object = cell->GetObject();
		if (object && !descriptor->CanSpawnOnObject(object->GetData()))
		{
			continue;
		}
		cell->SetObject(new Creature(descriptor, object));
		break;
	} while (true);
}

void RoomGenerator::PopulateCreatures()
{
	auto creatureTypes = creatureDescriptors.GetTypes();
	for (auto creatureType : creatureTypes)
	{
		auto descriptor = creatureDescriptors.GetDescriptor(creatureType);
		auto counter = descriptor->GetNumberAppearing();
		while (counter > 0)
		{
			SpawnCreature(descriptor);
			counter--;
		}
	}
}

void RoomGenerator::PlaceItem
(
	const ItemDescriptor* descriptor, 
	tggd::common::RoomCell<TerrainType, ObjectType, RoomCellFlags>* cell
)
{
	if (descriptor->GetProtectors().empty())
	{
		cell->SetObject(new Item(descriptor));
	}
	else
	{
		int index = tggd::common::Utility::GenerateRandomNumberFromRange(0, (int)descriptor->GetProtectors().size());
		CreatureType creatureType = descriptor->GetProtectors()[index];
		cell->SetObject(new Creature(creatureDescriptors.GetDescriptor(creatureType), new Item(descriptor)));
	}
}


void RoomGenerator::SpawnItem(const ItemDescriptor* descriptor)
{
	do
	{
		int column = tggd::common::Utility::GenerateRandomNumberFromRange(0, Constants::Room::COLUMNS);
		int row = tggd::common::Utility::GenerateRandomNumberFromRange(0, Constants::Room::ROWS);
		auto cell = room.GetCell(column, row);
		auto terrainType = cell->GetTerrain();
		if (cell->GetObject() || !descriptor->CanSpawnOnTerrain(terrainType))
		{
			continue;
		}
		PlaceItem(descriptor, cell);
		break;
	} while (true);
}


void RoomGenerator::PopulateLooseItems()
{
	auto itemTypes = itemDescriptors.GetTypes();
	for (auto itemType : itemTypes)
	{
		auto descriptor = itemDescriptors.GetDescriptor(itemType);
		auto counter = descriptor->GetNumberAppearing();
		while (counter > 0)
		{
			SpawnItem(descriptor);
			counter--;
		}
	}
}

void RoomGenerator::GenerateRoom()
{
	ScaffoldMaze();
	SmootheTerrain();
	PopulateLocks();
	PopulateKeys();
	PopulateDeadEnds();
	PopulateLooseItems();
	PopulateCreatures();
}

void RoomGenerator::PopulateLocks()
{
	for (auto& xy : GetDeadEnds())
	{
		size_t roomColumn = xy.GetX();
		size_t roomRow = xy.GetY();
		for (auto direction : RoomDirectionHelper::GetAll())
		{
			size_t nextRoomColumn = RoomDirectionHelper::GetNextColumn((int)roomColumn, (int)roomRow, direction);
			size_t nextRoomRow = RoomDirectionHelper::GetNextRow((int)roomColumn, (int)roomRow, direction);
			auto roomCell = room.GetCell(nextRoomColumn, nextRoomRow);
			if (TerrainTypeHelper::IsFloor(roomCell->GetTerrain()) && !roomCell->HasObject())
			{
				ItemType itemType =
					(direction == RoomDirection::EAST || direction == RoomDirection::WEST) ?
					(ItemType::DOOR_NS) :
					(ItemType::DOOR_EW);
				Item* item = new Item(itemDescriptors.GetDescriptor(itemType));
				roomCell->SetObject(item);
				break;
			}
		}
	}
}

void RoomGenerator::PopulateKeys()
{
	size_t keyCount = GetDeadEnds().size();
	while (keyCount > 0)
	{
		size_t roomColumn = tggd::common::Utility::GenerateRandomNumberFromRange(0, (int)room.GetColumns());
		size_t roomRow = tggd::common::Utility::GenerateRandomNumberFromRange(0, (int)room.GetRows());
		auto roomCell = room.GetCell(roomColumn, roomRow);
		if (!roomCell->HasObject() && roomCell->GetTerrain() == TerrainType::FLOOR)
		{

			Item* item = new Item(itemDescriptors.GetDescriptor(ItemType::KEY));
			roomCell->SetObject(item);
			keyCount--;
		}
	}
}

void RoomGenerator::PopulateDeadEndItem(ItemType itemType)
{
	do
	{
		size_t index = (size_t)tggd::common::Utility::GenerateRandomNumberFromRange(0, (int)GetDeadEnds().size());
		auto& xy = GetDeadEnds()[index];
		auto cell = room.GetCell(xy.GetX(), xy.GetY());
		if (cell->GetObject())
		{
			continue;
		}
		PlaceItem(itemDescriptors.GetDescriptor(itemType), cell);
		RemoveDeadEndAtIndex(index);
		break;
	} while (true);
}

void RoomGenerator::PopulateDeadEnds()
{
	auto itemTypes = itemDescriptors.GetTypes();
	for (auto& itemType : itemTypes)
	{
		auto descriptor = itemDescriptors.GetDescriptor(itemType);
		auto counter = descriptor->GetDeadEndAppearing();
		while (counter > 0)
		{
			PopulateDeadEndItem(itemType);
			counter--;
		}
	}
	while (!GetDeadEnds().empty())
	{
		PopulateDeadEndItem(ItemType::DIAMOND);
	}
}

void RoomGenerator::ClearRoom()
{
	for (int column = 0; column < room.GetColumns(); ++column)
	{
		for (int row = 0; row < room.GetRows(); ++row)
		{
			auto cell = room.GetCell(column, row);
			cell->RemoveObject();
			cell->ClearAllFlags();
			cell->SetFlag(RoomCellFlags::EXPLORED);//TODO: delete line
			bool isMazeCell = column % 2 == 1 && row % 2 == 1;//TODO: rewrite this to use PlotColumn/PlotRow
			cell->SetTerrain((isMazeCell) ? (TerrainType::FLOOR) : (TerrainType::WALL_NESW));
		}
	}
}

