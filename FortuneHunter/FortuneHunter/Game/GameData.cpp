#include "GameData.h"
#include "..\Constants\Room.h"
#include "Maze\Maze.h"
#include "..\Common\Utility.h"
GameData::GameData()
	: room(Constants::Room::COLUMNS, Constants::Room::ROWS)
	, hunter(nullptr)
{
	for (int column = 0; column < room.GetColumns(); ++column)
	{
		for (int row = 0; row < room.GetRows(); ++row)
		{
			room.GetCell(column, row)->SetTerrain((column % 2 == 1 && row % 2 == 1) ? (Terrain::FLOOR) : (Terrain::WALL_NESW));
		}
	}
	tggd::common::Utility::SeedRandomNumberGenerator();
	Maze maze(Constants::Maze::COLUMNS, Constants::Maze::ROWS);
	maze.Generate();
	for (int column = 0; column < maze.GetColumns(); ++column)
	{
		for (int row = 0; row < maze.GetRows(); ++row)
		{
			MazeCell* cell = maze.GetCell(column, row);
			if (cell->HasDoor(MazeDirection::EAST) && cell->GetDoor(MazeDirection::EAST)->IsOpen())
			{
				room.GetCell((size_t)column * 2 + 2, (size_t)row * 2 + 1)->SetTerrain(Terrain::FLOOR);
			}
			if (cell->HasDoor(MazeDirection::SOUTH) && cell->GetDoor(MazeDirection::SOUTH)->IsOpen())
			{
				room.GetCell((size_t)column * 2 + 1, (size_t)row * 2 + 2)->SetTerrain(Terrain::FLOOR);
			}
		}
	}
	static Terrain flagMap[16] =
	{
		Terrain::FLOOR,
		Terrain::WALL_N,
		Terrain::WALL_E,
		Terrain::WALL_NE,
		Terrain::WALL_S,
		Terrain::WALL_NS,
		Terrain::WALL_ES,
		Terrain::WALL_NES,
		Terrain::WALL_W,
		Terrain::WALL_NW,
		Terrain::WALL_EW,
		Terrain::WALL_NEW,
		Terrain::WALL_SW,
		Terrain::WALL_NSW,
		Terrain::WALL_ESW,
		Terrain::WALL_NESW
	};
	for (int column = 0; column < room.GetColumns(); ++column)
	{
		for (int row = 0; row < room.GetRows(); ++row)
		{
			RoomCell* cell = room.GetCell(column, row);
			int flags = 0;
			if (cell->GetTerrain() != Terrain::FLOOR)
			{
				if (row == 0 || room.GetCell(column, (size_t)row - 1)->GetTerrain() != Terrain::FLOOR)
				{
					flags |= 1;
				}
				if (row == Constants::Room::ROWS - 1 || room.GetCell(column, (size_t)row + 1)->GetTerrain() != Terrain::FLOOR)
				{
					flags |= 4;
				}
				if (column == 0 || room.GetCell((size_t)column - 1, row)->GetTerrain() != Terrain::FLOOR)
				{
					flags |= 8;
				}
				if (column == Constants::Room::COLUMNS - 1 || room.GetCell((size_t)column+1, row)->GetTerrain() != Terrain::FLOOR)
				{
					flags |= 2;
				}
			}
			cell->SetTerrain(flagMap[flags]);
		}
	}
	hunter = new Creature(CreatureType::HUNTER);
	while (hunter->GetRoomCell() == nullptr)
	{
		int column = tggd::common::Utility::GenerateRandomNumberFromRange(0, Constants::Room::COLUMNS);
		int row = tggd::common::Utility::GenerateRandomNumberFromRange(0, Constants::Room::ROWS);
		if (room.GetCell(column, row)->GetTerrain() == Terrain::FLOOR)
		{
			room.GetCell(column, row)->SetCreature(hunter);
		}
	}
}

const Room& GameData::GetRoom() const
{
	return room;
}

Room& GameData::GetRoom()
{
	return room;
}

const Creature* GameData::GetHunter() const
{
	return hunter;
}

Creature* GameData::GetHunter()
{
	return hunter;
}
