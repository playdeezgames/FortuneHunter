#pragma once
#include <vector>
#include "RoomCell.h"
class Room
{
private:
	size_t columns;
	size_t rows;
	std::vector<RoomCell*> cells;
public:
	Room(size_t, size_t);
	~Room();
	RoomCell* GetCell(size_t, size_t) const;
};
