#include "MazeDirection.h"
#include <string>
std::vector<MazeDirection> allDirections;
const std::vector<MazeDirection>& MazeDirectionHelper::GetAll()
{
	if (allDirections.empty())
	{
		allDirections.push_back(MazeDirection::NORTH);
		allDirections.push_back(MazeDirection::EAST);
		allDirections.push_back(MazeDirection::SOUTH);
		allDirections.push_back(MazeDirection::WEST);
	}
	return allDirections;
}
MazeDirection MazeDirectionHelper::GetOpposite(MazeDirection direction)
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

int MazeDirectionHelper::GetNextColumn(int column, int row, MazeDirection direction)
{
	switch (direction)
	{
	case MazeDirection::EAST:
		return column + 1;
	case MazeDirection::WEST:
		return column - 1;
	case MazeDirection::NORTH:
		return column;
	case MazeDirection::SOUTH:
		return column;
	default:
		throw std::string("bad direction");
	}
}

int MazeDirectionHelper::GetNextRow(int column, int row, MazeDirection direction)
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