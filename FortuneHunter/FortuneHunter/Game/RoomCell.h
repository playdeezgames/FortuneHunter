#pragma once
#include "Terrain.h"
class RoomCell
{
private:
	Terrain terrain;
public:
	RoomCell();
	Terrain GetTerrain() const;
	void SetTerrain(Terrain);
};
