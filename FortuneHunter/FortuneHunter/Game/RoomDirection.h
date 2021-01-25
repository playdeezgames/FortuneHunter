#pragma once
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
};