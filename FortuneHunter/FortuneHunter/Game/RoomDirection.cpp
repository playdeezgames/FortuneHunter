#include "RoomDirection.h"
#include <string>
int RoomDirectionHelper::GetNextColumn(int column, int row, RoomDirection direction)
{
	switch (direction)
	{
	case RoomDirection::EAST:
		return column + 1;
	case RoomDirection::WEST:
		return column - 1;
	case RoomDirection::NORTH:
		return column;
	case RoomDirection::SOUTH:
		return column;
	default:
		throw std::string("bad direction");
	}
}

int RoomDirectionHelper::GetNextRow(int column, int row, RoomDirection direction)
{
	switch (direction)
	{
	case RoomDirection::EAST:
		return row;
	case RoomDirection::WEST:
		return row;
	case RoomDirection::NORTH:
		return row - 1;
	case RoomDirection::SOUTH:
		return row + 1;
	default:
		throw std::string("bad direction");
	}
}