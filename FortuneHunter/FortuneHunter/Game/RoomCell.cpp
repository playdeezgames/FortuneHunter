#include "RoomCell.h"
RoomCell::RoomCell()
	: terrain(Terrain::FLOOR)
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
