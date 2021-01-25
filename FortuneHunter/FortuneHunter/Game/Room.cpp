#include "Room.h"
Room::Room(size_t columns, size_t rows)
	: columns(columns)
	, rows(rows)
	, cells()
{
	for (size_t row = 0; row < rows; ++row)
	{
		for (size_t column = 0; column < columns; ++column)
		{
			cells.push_back(new RoomCell(column, row));
		}
	}
}

Room::~Room()
{
	for (auto& item : cells)
	{
		if (item)
		{
			delete item;
			item = nullptr;
		}
	}
}


const RoomCell* Room::GetCell(size_t column, size_t row) const
{
	return cells[column + row * columns];
}

RoomCell* Room::GetCell(size_t column, size_t row)
{
	return cells[column + row * columns];
}

size_t Room::GetColumns() const
{
	return columns;
}

size_t Room::GetRows() const
{
	return rows;
}
