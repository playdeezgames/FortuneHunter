#include "GameData.h"
#include "..\Constants\Room.h"
#include "Maze\Maze.h"
#include "..\Common\Utility.h"
GameData::GameData()
	: room(Constants::Room::COLUMNS, Constants::Room::ROWS, TerrainType::FLOOR)
	, hunter(nullptr)
{
}

void GameData::ClearHunter()
{
	if (hunter)
	{
		if (hunter->GetRoomCell())
		{
			hunter->GetRoomCell()->SetCreature(nullptr);
		}
		delete hunter;
	}
	hunter = nullptr;
}


GameData::~GameData()
{
	ClearHunter();
}


const Room<TerrainType, ItemType, CreatureType>& GameData::GetRoom() const
{
	return room;
}

Room<TerrainType, ItemType, CreatureType>& GameData::GetRoom()
{
	return room;
}

const Creature<TerrainType, CreatureType>* GameData::GetHunter() const
{
	return hunter;
}

Creature<TerrainType, CreatureType>* GameData::GetHunter()
{
	return hunter;
}

void GameData::ClearRoom()
{
	ClearHunter();
	for (int column = 0; column < room.GetColumns(); ++column)
	{
		for (int row = 0; row < room.GetRows(); ++row)
		{
			room.GetCell(column, row)->SetTerrain((column % 2 == 1 && row % 2 == 1) ? (TerrainType::FLOOR) : (TerrainType::WALL_NESW));
		}
	}
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

void GameData::ScaffoldMaze()
{
	ClearRoom();
	Maze maze(Constants::Maze::COLUMNS, Constants::Maze::ROWS);
	maze.Generate();
	for (int column = 0; column < maze.GetColumns(); ++column)
	{
		for (int row = 0; row < maze.GetRows(); ++row)
		{
			MazeCell* cell = maze.GetCell(column, row);
			if (cell->HasDoor(MazeDirection::EAST) && cell->GetDoor(MazeDirection::EAST)->IsOpen())
			{
				room.GetCell((size_t)column * 2 + 2, (size_t)row * 2 + 1)->SetTerrain(TerrainType::FLOOR);
			}
			if (cell->HasDoor(MazeDirection::SOUTH) && cell->GetDoor(MazeDirection::SOUTH)->IsOpen())
			{
				room.GetCell((size_t)column * 2 + 1, (size_t)row * 2 + 2)->SetTerrain(TerrainType::FLOOR);
			}
		}
	}
}	

void GameData::FlagifyCell(int column, int row)
{
	RoomCell<TerrainType, CreatureType>* cell = room.GetCell(column, row);
	int flags = 0;
	if (cell->GetTerrain() != TerrainType::FLOOR)
	{
		if (row == 0 || room.GetCell(column, (size_t)row - 1)->GetTerrain() != TerrainType::FLOOR)
		{
			flags |= 1;
		}
		if (column == Constants::Room::COLUMNS - 1 || room.GetCell((size_t)column + 1, row)->GetTerrain() != TerrainType::FLOOR)
		{
			flags |= 2;
		}
		if (row == Constants::Room::ROWS - 1 || room.GetCell(column, (size_t)row + 1)->GetTerrain() != TerrainType::FLOOR)
		{
			flags |= 4;
		}
		if (column == 0 || room.GetCell((size_t)column - 1, row)->GetTerrain() != TerrainType::FLOOR)
		{
			flags |= 8;
		}
	}
	cell->SetTerrain(flagMap[flags]);
}


void GameData::SmootheTerrain()
{
	for (int column = 0; column < room.GetColumns(); ++column)
	{
		for (int row = 0; row < room.GetRows(); ++row)
		{
			FlagifyCell(column, row);
		}
	}
}

void GameData::GenerateRoom()
{
	ScaffoldMaze();
	SmootheTerrain();
}


void GameData::Start()
{
	GenerateRoom();
	hunter = new Creature<TerrainType, CreatureType>(CreatureType::HUNTER);
	while (hunter->GetRoomCell() == nullptr)
	{
		int column = tggd::common::Utility::GenerateRandomNumberFromRange(0, Constants::Room::COLUMNS);
		int row = tggd::common::Utility::GenerateRandomNumberFromRange(0, Constants::Room::ROWS);
		if (room.GetCell(column, row)->GetTerrain() == TerrainType::FLOOR)
		{
			room.GetCell(column, row)->SetCreature(hunter);
		}
	}
	UpdateRoom();
}

void GameData::UpdateRoom()
{
	for (size_t column = 0; column < room.GetColumns(); ++column)
	{
		for (size_t row = 0; row < room.GetRows(); ++row)
		{
			room.GetCell(column, row)->SetLit(false);
		}
	}
	if (hunter && hunter->GetRoomCell())
	{
		int column = (int)hunter->GetRoomCell()->GetColumn();
		int row = (int)hunter->GetRoomCell()->GetRow();
		for (int c = column - 1; c <= column + 1; ++c)
		{
			for (int r = row - 1; r <= row + 1; ++r)
			{
				auto cell = room.GetCell(c, r);
				if (cell)
				{
					cell->SetLit(true);
					cell->SetExplored(true);
				}
			}
		}
	}
}
