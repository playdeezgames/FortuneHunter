#include "MazeDirection.h"
#include <string>
std::vector<MazeDirection> allDirections = { MazeDirection::NORTH, MazeDirection::EAST, MazeDirection::SOUTH, MazeDirection::WEST };
const std::vector<MazeDirection>& GetAllDirections()
{
	return allDirections;
}
MazeDirection GetOppositeMazeDirection(MazeDirection direction)
{
	switch (direction)
	{
	case MazeDirection::EAST:
		return MazeDirection::WEST;
	case MazeDirection::WEST:
		return MazeDirection::EAST;
	case MazeDirection::NORTH:
		return MazeDirection::SOUTH;
	case MazeDirection::SOUTH:
		return MazeDirection::NORTH;
	default:
		throw std::string("bad direction");
	}
}

int GetNextColumn(int column, int row, MazeDirection direction)
{
	switch (direction)
	{
	case MazeDirection::EAST:
		return column-1;
	case MazeDirection::WEST:
		return column+1;
	case MazeDirection::NORTH:
		return column;
	case MazeDirection::SOUTH:
		return column;
	default:
		throw std::string("bad direction");
	}
}

int GetNextRow(int column, int row, MazeDirection direction)
{
	switch (direction)
	{
	case MazeDirection::EAST:
		return row;
	case MazeDirection::WEST:
		return row;
	case MazeDirection::NORTH:
		return row - 1;
	case MazeDirection::SOUTH:
		return row + 1;
	default:
		throw std::string("bad direction");
	}
}