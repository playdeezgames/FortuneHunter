#pragma once
#include "..\..\Common\XY.h"
#include <vector>
class RoomGenerationContext
{
private:
	std::vector<tggd::common::XY<size_t>> deadEnds;
public:
	RoomGenerationContext();
	const std::vector<tggd::common::XY<size_t>>& GetDeadEnds() const;
	void AddDeadEnd(const tggd::common::XY<size_t>&);
};
