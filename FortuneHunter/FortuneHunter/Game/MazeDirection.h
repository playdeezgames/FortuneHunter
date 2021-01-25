#pragma once
#include <vector>
enum class MazeDirection
{
	NORTH,
	EAST,
	SOUTH,
	WEST
};
class MazeDirectionHelper
{
public:
	static MazeDirection GetOpposite(MazeDirection);
	static const std::vector<MazeDirection>& GetAll();
	static int GetNextColumn(int, int, MazeDirection);
	static int GetNextRow(int, int, MazeDirection);
};