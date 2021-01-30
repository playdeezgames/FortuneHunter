#include "RoomGenerationContext.h"
RoomGenerationContext::RoomGenerationContext()
	: deadEnds()
{

}

const std::vector<tggd::common::XY<size_t>>& RoomGenerationContext::GetDeadEnds() const
{
	return deadEnds;
}

void RoomGenerationContext::AddDeadEnd(const tggd::common::XY<size_t>& xy)
{
	deadEnds.push_back(xy);
}

void RoomGenerationContext::RemoveDeadEndAtIndex(size_t index)
{
	deadEnds.erase(deadEnds.begin() + index);
}
