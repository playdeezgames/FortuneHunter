#include "Maze.h"
Maze::Maze(size_t columns, size_t rows)
	: cells()
	, doors()
	, columns(columns)
	, rows(rows)
{
	while (cells.size() < columns * rows)
	{
		cells.push_back(new MazeCell());
	}
	for (int column = 0; column < columns; ++column)
	{
		for(int row = 0; row<rows; ++row)
		{ 
			MazeCell* cell = GetCell(column, row);
			for (auto direction : GetAllDirections())
			{
				if (!cell->HasNeighbor(direction))
				{
					int nextColumn = GetNextColumn(column, row, direction);
					int nextRow = GetNextRow(column, row, direction);
					if (nextColumn >= 0 && nextColumn < columns && nextRow >= 0 && nextRow < row)
					{
						MazeCell* neighbor = GetCell(column, row);
						MazeDoor* door = new MazeDoor();
						doors.push_back(door);
						cell->SetNeighbor(direction, neighbor);
						cell->SetDoor(direction, door);
						neighbor->SetNeighbor(GetOppositeMazeDirection(direction), cell);
						neighbor->SetDoor(GetOppositeMazeDirection(direction), door);
					}
				}
			}
		}
	}
}

Maze::~Maze()
{
	for (auto& ptr : cells)
	{
		delete ptr;
	}
	for (auto& ptr : doors)
	{
		delete ptr;
	}
}

MazeCell* Maze::GetCell(int column, int row)
{
	if (column >= 0 && column < columns && row >= 0 && row < rows)
	{
		return cells[column + row * columns];
	}
	return nullptr;
}

const MazeCell* Maze::GetCell(int column, int row) const
{
	if (column >= 0 && column < columns && row >= 0 && row < rows)
	{
		return cells[column + row * columns];
	}
	return nullptr;
}
