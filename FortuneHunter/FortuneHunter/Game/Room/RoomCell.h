#pragma once
#include "Terrain.h"
#include "Creature.h"
class RoomCell
{
private:
	Terrain terrain;
	Creature* creature;
	size_t column;
	size_t row;
public:
	RoomCell(size_t, size_t);
	~RoomCell();
	Terrain GetTerrain() const;
	void SetTerrain(Terrain);
	void SetCreature(Creature*);
	const Creature* GetCreature() const;
	Creature* GetCreature();
	size_t GetColumn() const;
	size_t GetRow() const;
};
