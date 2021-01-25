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
	const RoomCell* GetCell(size_t, size_t) const;
	RoomCell* GetCell(size_t, size_t);
	size_t GetColumns() const;
	size_t GetRows() const;
};