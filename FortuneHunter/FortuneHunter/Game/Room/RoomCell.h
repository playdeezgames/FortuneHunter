#pragma once
#include "Terrain.h"
#include "Creature.h"
template<typename TCreatureData>
class RoomCell
{
private:
	Terrain terrain;
	Creature<TCreatureData>* creature;
	bool explored;
	bool lit;
	size_t column;
	size_t row;
public:
	RoomCell(size_t column, size_t row)
		: terrain(Terrain::FLOOR)
		, creature(nullptr)
		, column(column)
		, row(row)
		, explored(false)
		, lit(false)
	{}
	~RoomCell()
	{
		if (creature)
		{
			delete creature;
			creature = nullptr;
		}
	}
	Terrain GetTerrain() const { return terrain; }
	void SetTerrain(Terrain newTerrain) { terrain = newTerrain; }
	void SetCreature(Creature<TCreatureData>* newCreature)
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
	const Creature<TCreatureData>* GetCreature() const { return creature; }
	Creature<TCreatureData>* GetCreature() { return creature; }
	size_t GetColumn() const { return column; }
	size_t GetRow() const { return row; }
	bool IsLit() const { return lit; }
	bool IsExplored() const { return explored; }
	void SetLit(bool state) { lit = state; }
	void SetExplored(bool state) { explored = state; }
};
