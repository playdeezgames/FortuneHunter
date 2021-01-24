#include "GameData.h"
#include "..\Constants\Room.h"
#include "Maze.h"
GameData::GameData()
	: room(Constants::Room::COLUMNS, Constants::Room::ROWS)
{
	for (int column = 0; column < room.GetColumns(); ++column)
	{
		for (int row = 0; row < room.GetRows(); ++row)
		{
			room.GetCell(column, row).SetTerrain((column % 2 == 1 && row % 2 == 1) ? (Terrain::FLOOR) : (Terrain::WALL));
		}
	}
	Maze maze(Constants::Maze::COLUMNS, Constants::Maze::ROWS);
	maze.Generate();
	for (int column = 0; column < maze.GetColumns(); ++column)
	{
		for (int row = 0; row < maze.GetRows(); ++row)
		{
			MazeCell* cell = maze.GetCell(column, row);
			if (cell->HasDoor(MazeDirection::EAST) && cell->GetDoor(MazeDirection::EAST)->IsOpen())
			{
				room.GetCell(column * 2 + 2, row * 2 + 1).SetTerrain(Terrain::FLOOR);
			}
			if (cell->HasDoor(MazeDirection::SOUTH) && cell->GetDoor(MazeDirection::SOUTH)->IsOpen())
			{
				room.GetCell(column * 2 + 1, row * 2 + 2).SetTerrain(Terrain::FLOOR);
			}
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
