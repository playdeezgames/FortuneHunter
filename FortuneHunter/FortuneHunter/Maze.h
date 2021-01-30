#pragma once
#include <vector>
#include "MazeCell.h"
#include "MazeDoor.h"
class Maze
{
private:
	size_t columns;
	size_t rows;
	std::vector<MazeCell*> cells;
	std::vector<MazeDoor*> doors;
	void Clear();
	void PopulateCells();
	void InitializeCells();
	void InitializeCell(int, int);
public:
	Maze(size_t, size_t);
	~Maze();
	MazeCell* GetCell(int, int);
	const MazeCell* GetCell(int, int) const;
	void Generate();
	size_t GetColumns() const;
	size_t GetRows() const;
};
