#include "RoomDirection.h"
#include <string>
std::vector<RoomDirection> allDirections;
const std::vector<RoomDirection>& RoomDirectionHelper::GetAll()
{
	if (allDirections.empty())
	{
		allDirections.push_back(RoomDirection::NORTH);
		allDirections.push_back(RoomDirection::EAST);
		allDirections.push_back(RoomDirection::SOUTH);
		allDirections.push_back(RoomDirection::WEST);
	}
	return allDirections;
}


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