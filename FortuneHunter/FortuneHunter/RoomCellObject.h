#pragma once
namespace tggd::common
{
	template<typename TTerrain, typename TObjectData>
	class RoomCell;
	template<typename TTerrain, typename TObjectData>
	class RoomCellObject
	{
	private:
		friend class RoomCell<TTerrain, TObjectData>;
		RoomCell<TTerrain, TObjectData>* roomCell;
	public:
		RoomCellObject() :roomCell(nullptr) {}
		const RoomCell<TTerrain, TObjectData>* GetRoomCell() const { return roomCell; }
		RoomCell<TTerrain, TObjectData>* GetRoomCell() { return roomCell; }
		virtual const TObjectData& GetData() const = 0;
	};
}