#pragma once
#include "RoomCellObject.h"
namespace tggd::common
{
	template<typename TTerrain, typename TObjectData, typename TCellFlags>
	class RoomCell
	{
	private:
		TTerrain terrain;
		RoomCellObject<TTerrain, TObjectData, TCellFlags>* object;
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
			//, explored(true)
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
		void SetObject(RoomCellObject<TTerrain, TObjectData, TCellFlags>* newCreature)
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
		const RoomCellObject<TTerrain, TObjectData, TCellFlags>* GetObject() const { return object; }
		RoomCellObject<TTerrain, TObjectData, TCellFlags>* GetObject() { return object; }
		bool HasObject() const { return object != nullptr; }
		size_t GetColumn() const { return column; }
		size_t GetRow() const { return row; }
		bool IsLit() const { return lit; }
		bool IsExplored() const { return explored; }
		void SetLit(bool state) { lit = state; }
		void SetExplored(bool state) { explored = state; }
		void RemoveObject()
		{
			if (object)
			{
				SetObject(nullptr);
				delete object;
			}
		}
	};

}