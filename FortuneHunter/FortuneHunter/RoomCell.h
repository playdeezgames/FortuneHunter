#pragma once
#include "RoomCellObject.h"
#include <set>
#include "Utility.h"
namespace tggd::common
{
	template<typename TTerrain, typename TObjectData, typename TCellFlags>
	class RoomCell
	{
	private:
		TTerrain terrain;
		RoomCellObject<TTerrain, TObjectData, TCellFlags>* object;
		size_t column;
		size_t row;
		std::set<TCellFlags> cellFlags;
	public:
		RoomCell(size_t column, size_t row, const TTerrain& terrain)
			: terrain(terrain)
			, object(nullptr)
			, column(column)
			, row(row)
			, cellFlags()
		{}
		~RoomCell()
		{
			if (object)
			{
				Utility::SafeDelete(object);
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
		void SetFlag(const TCellFlags& flag)
		{
			cellFlags.insert(flag);
		}
		void ClearFlag(const TCellFlags& flag)
		{
			cellFlags.erase(flag);
		}
		bool IsFlagSet(const TCellFlags& flag) const
		{
			return cellFlags.contains(flag);
		}
		void RemoveObject()
		{
			if (object)
			{
				SetObject(nullptr);
				delete object;
			}
		}
		void ClearAllFlags()
		{
			cellFlags.clear();
		}
	};

}