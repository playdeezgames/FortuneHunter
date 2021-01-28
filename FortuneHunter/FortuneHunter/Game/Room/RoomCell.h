#pragma once
#include "RoomCellObject.h"
template<typename TTerrain, typename TObjectData>
class RoomCell
{
private:
	TTerrain terrain;
	RoomCellObject<TTerrain, TObjectData>* object;
	bool explored;
	bool lit;
	size_t column;
	size_t row;
public:
	RoomCell(size_t column, size_t row, const TTerrain& terrain)
		: terrain(terrain)
		, object(nullptr)
		, column(column)
		, row(row)
		, explored(false)
		, lit(false)
	{}
	~RoomCell()
	{
		if (object)
		{
			delete object;
			object = nullptr;
		}
	}
	const TTerrain& GetTerrain() const { return terrain; }
	void SetTerrain(const TTerrain& newTerrain) { terrain = newTerrain; }
	void SetObject(RoomCellObject<TTerrain, TObjectData>* newCreature)
	{
		if (object)
		{
			object->roomCell = nullptr;
		}
		object = newCreature;
		if (object)
		{
			object->roomCell = this;
		}
	}
	const RoomCellObject<TTerrain, TObjectData>* GetObject() const { return object; }
	RoomCellObject<TTerrain, TObjectData>* GetObject() { return object; }
	bool HasObject() const { return object != nullptr; }
	size_t GetColumn() const { return column; }
	size_t GetRow() const { return row; }
	bool IsLit() const { return lit; }
	bool IsExplored() const { return explored; }
	void SetLit(bool state) { lit = state; }
	void SetExplored(bool state) { explored = state; }
};
