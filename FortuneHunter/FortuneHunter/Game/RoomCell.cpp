#include "RoomCell.h"
RoomCell::RoomCell()
	: terrain(Terrain::FLOOR)
	, creature(nullptr)
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
