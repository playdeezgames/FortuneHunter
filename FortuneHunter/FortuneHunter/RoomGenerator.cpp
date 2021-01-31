#include "RoomGenerator.h"
RoomGenerator::RoomGenerator()
	: deadEnds()
{

}

const std::vector<tggd::common::XY<size_t>>& RoomGenerator::GetDeadEnds() const
{
	return deadEnds;
}

void RoomGenerator::AddDeadEnd(const tggd::common::XY<size_t>& xy)
{
	deadEnds.push_back(xy);
}

void RoomGenerator::RemoveDeadEndAtIndex(size_t index)
{
	deadEnds.erase(deadEnds.begin() + index);
}
