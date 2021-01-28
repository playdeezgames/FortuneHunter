#pragma once
template<typename TTerrain, typename TObjectData>
class RoomCell;
template<typename TTerrain, typename TObjectData>
class RoomCellObject
{
private:
	friend class RoomCell<TTerrain, TObjectData>;
	RoomCell<TTerrain, TObjectData>* roomCell;
	TObjectData objectData;
public:
	RoomCellObject(TObjectData creatureData) :roomCell(nullptr), objectData(creatureData) {}
	const RoomCell<TTerrain, TObjectData>* GetRoomCell() const { return roomCell; }
	RoomCell<TTerrain, TObjectData>* GetRoomCell() { return roomCell; }
	const TObjectData& GetObjectData() const { return objectData; }
};
