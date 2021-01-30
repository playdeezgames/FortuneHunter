#pragma once
namespace tggd::common
{
	template<typename TTerrain, typename TObjectData, typename TCellFlags>
	class RoomCell;
	template<typename TTerrain, typename TObjectData, typename TCellFlags>
	class RoomCellObject
	{
	private:
		friend class RoomCell<TTerrain, TObjectData, TCellFlags>;
		RoomCell<TTerrain, TObjectData, TCellFlags>* roomCell;
	public:
		RoomCellObject() :roomCell(nullptr) {}
		virtual ~RoomCellObject() {}
		const RoomCell<TTerrain, TObjectData, TCellFlags>* GetRoomCell() const { return roomCell; }
		RoomCell<TTerrain, TObjectData, TCellFlags>* GetRoomCell() { return roomCell; }
		virtual const TObjectData& GetData() const = 0;
	};
}