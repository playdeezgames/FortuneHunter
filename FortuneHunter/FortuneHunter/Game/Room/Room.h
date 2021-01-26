#pragma once
#include <vector>
#include "RoomCell.h"
template<typename TCreatureData>
class Room
{
private:
	size_t columns;
	size_t rows;
	std::vector<RoomCell<TCreatureData>*> cells;
public:
	Room(size_t columns, size_t rows)
		: columns(columns)
		, rows(rows)
		, cells()
	{
		for (size_t row = 0; row < rows; ++row)
		{
			for (size_t column = 0; column < columns; ++column)
			{
				cells.push_back(new RoomCell<TCreatureData>(column, row));
			}
		}
	}

	~Room()
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
	const RoomCell<TCreatureData>* GetCell(size_t column, size_t row) const
	{
		if (column < columns && row < rows)
		{
			return cells[column + row * columns];
		}
		return nullptr;
	}
	RoomCell<TCreatureData>* GetCell(size_t column, size_t row)
	{
		if (column < columns && row < rows)
		{
			return cells[column + row * columns];
		}
		return nullptr;
	}
	size_t GetColumns() const { return columns; }
	size_t GetRows() const { return rows; }
};
