#pragma once
#include "XY.h"
#include <vector>
class RoomGenerator
{
private:
	std::vector<tggd::common::XY<size_t>> deadEnds;
public:
	RoomGenerator();
	const std::vector<tggd::common::XY<size_t>>& GetDeadEnds() const;
	void AddDeadEnd(const tggd::common::XY<size_t>&);
	void RemoveDeadEndAtIndex(size_t);
};
