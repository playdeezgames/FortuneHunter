#include "RoomCell.h"
RoomCell::RoomCell(size_t column, size_t row)
	: terrain(Terrain::FLOOR)
	, creature(nullptr)
	, column(column)
	, row(row)
{

}

Terrain RoomCell::GetTerrain() const
{
	return terrain;
}

void RoomCell::SetTerrain(Terrain newTerrain)
{
	terrain = newTerrain;
}

void RoomCell::SetCreature(Creature* newCreature)
{
	if (creature)
	{
		creature->roomCell = nullptr;
	}
	creature = newCreature;
	if (creature)
	{
		creature->roomCell = this;
	}
}

const Creature* RoomCell::GetCreature() const
{
	return creature;
}

Creature* RoomCell::GetCreature()
{
	return creature;
}

size_t RoomCell::GetColumn() const
{
	return column;
}

size_t RoomCell::GetRow() const
{
	return row;
}

RoomCell::~RoomCell()
{
	if (creature)
	{
		delete creature;
		creature = nullptr;
	}
}
