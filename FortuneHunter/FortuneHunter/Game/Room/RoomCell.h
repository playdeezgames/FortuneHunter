#pragma once
#include "Creature.h"
template<typename TTerrain, typename TCreatureData>
class RoomCell
{
private:
	TTerrain terrain;
	Creature<TTerrain, TCreatureData>* creature;
	bool explored;
	bool lit;
	size_t column;
	size_t row;
public:
	RoomCell(size_t column, size_t row, const TTerrain& terrain)
		: terrain(terrain)
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
	const TTerrain& GetTerrain() const { return terrain; }
	void SetTerrain(const TTerrain& newTerrain) { terrain = newTerrain; }
	void SetCreature(Creature<TTerrain, TCreatureData>* newCreature)
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
	const Creature<TTerrain, TCreatureData>* GetCreature() const { return creature; }
	Creature<TTerrain, TCreatureData>* GetCreature() { return creature; }
	size_t GetColumn() const { return column; }
	size_t GetRow() const { return row; }
	bool IsLit() const { return lit; }
	bool IsExplored() const { return explored; }
	void SetLit(bool state) { lit = state; }
	void SetExplored(bool state) { explored = state; }
};
