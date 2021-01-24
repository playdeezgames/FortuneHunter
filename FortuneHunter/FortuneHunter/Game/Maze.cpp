#include "Maze.h"
#include <set>
#include "..\Common\Utility.h"
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

void Maze::Clear()
{
	for (auto& door : doors)
	{
		door->SetOpen(false);
	}
}

void Maze::Generate()
{
	Clear();
	std::set<MazeCell*> outside(cells.begin(), cells.end());
	std::vector<MazeCell*> frontier;
	std::set<MazeCell*> inside;
	MazeCell* cell = cells[tggd::common::Utility::GenerateRandomNumberFromRange(0, (int)cells.size())];
	outside.erase(cell);
	inside.insert(cell);
	for (auto direction : GetAllDirections())
	{
		if (cell->HasNeighbor(direction))
		{
			MazeCell* neighbor = cell->GetNeighbor(direction);
			outside.erase(neighbor);
			frontier.push_back(neighbor);
		}
	}
	while (!frontier.empty())
	{
		size_t index = tggd::common::Utility::GenerateRandomNumberFromRange(0, (int)frontier.size());
		cell = frontier[index];
		frontier[index] = frontier[frontier.size() - 1];
		frontier.pop_back();
		std::vector<MazeDirection> candidates;
		for (auto direction : GetAllDirections())
		{
			if (cell->HasNeighbor(direction))
			{
				MazeCell* neighbor = cell->GetNeighbor(direction);
				if (inside.contains(neighbor))
				{
					candidates.push_back(direction);
				}
			}
		}
		MazeDirection direction = candidates[tggd::common::Utility::GenerateRandomNumberFromRange(0, (int)candidates.size())];
		cell->GetDoor(direction)->SetOpen(true);
		inside.insert(cell);
		for (auto direction : GetAllDirections())
		{
			if (cell->HasNeighbor(direction))
			{
				MazeCell* neighbor = cell->GetNeighbor(direction);
				if (outside.contains(neighbor))
				{
					outside.erase(neighbor);
					frontier.push_back(neighbor);
				}
			}
		}
	}
}
