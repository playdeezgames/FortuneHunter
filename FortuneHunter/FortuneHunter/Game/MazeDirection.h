#pragma once
#include <vector>
enum class MazeDirection
{
	NORTH,
	EAST,
	SOUTH,
	WEST
};
MazeDirection GetOppositeMazeDirection(MazeDirection);
const std::vector<MazeDirection>& GetAllDirections();
int GetNextColumn(int, int, MazeDirection);
int GetNextRow(int, int, MazeDirection);