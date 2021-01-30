#pragma once
#include <vector>
enum class RoomDirection
{
	NORTH,
	EAST,
	SOUTH,
	WEST
};
class RoomDirectionHelper
{
public:
	static int GetNextColumn(int, int, RoomDirection);
	static int GetNextRow(int, int, RoomDirection);
	static const std::vector<RoomDirection>& GetAll();

};