#pragma once
#include "MazeDirection.h"
#include "MazeDoor.h"
#include <map>
#include <vector>
class MazeCell
{
private:
	std::map<MazeDirection, MazeDoor*> exits;
	std::map<MazeDirection, MazeCell*> neighbors;
public:
	MazeCell();
	void SetNeighbor(MazeDirection, MazeCell*);
	void SetDoor(MazeDirection, MazeDoor*);
	const MazeCell* GetNeighbor(MazeDirection) const;
	MazeCell* GetNeighbor(MazeDirection);
	const MazeDoor* GetDoor(MazeDirection) const;
	MazeDoor* GetDoor(MazeDirection);
	bool HasDoor(MazeDirection) const;
	bool HasNeighbor(MazeDirection) const;
	bool IsDeadEnd() const;
};
