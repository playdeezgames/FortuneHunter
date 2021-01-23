#include "Room.h"
Room::Room(size_t columns, size_t rows)
	: columns(columns)
	, rows(rows)
	, cells(columns * rows)
{
	while (cells.size() < columns * rows)
	{
		cells.push_back(new RoomCell());
	}
}

Room::~Room()
{
	for (auto& cell : cells)
	{
		delete cell;
		cell = nullptr;
	}
}

RoomCell* Room::GetCell(size_t column, size_t row) const
{
	if (column < columns && row < rows)
	{
		return cells[column + row * columns];
	}
	return nullptr;
}
