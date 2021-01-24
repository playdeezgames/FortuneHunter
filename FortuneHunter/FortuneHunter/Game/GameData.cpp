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
}

const Room& GameData::GetRoom() const
{
	return room;
}

Room& GameData::GetRoom()
{
	return room;
}
