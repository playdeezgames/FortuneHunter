#include "Room.h"
Room::Room(size_t columns, size_t rows)
	: columns(columns)
	, rows(rows)
	, cells(columns * rows)
{
	while (cells.size() < columns * rows)
	{
		cells.push_back(RoomCell());
	}
}

const RoomCell& Room::GetCell(size_t column, size_t row) const
{
	return cells[column + row * columns];
}

RoomCell& Room::GetCell(size_t column, size_t row)
{
	return cells[column + row * columns];
}

