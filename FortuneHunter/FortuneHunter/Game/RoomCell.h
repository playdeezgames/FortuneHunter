#pragma once
#include "Terrain.h"
#include "Creature.h"
class RoomCell
{
private:
	Terrain terrain;
	Creature* creature;
public:
	RoomCell();
	Terrain GetTerrain() const;
	void SetTerrain(Terrain);
	void SetCreature(Creature*);
	const Creature* GetCreature() const;
	Creature* GetCreature();
};
