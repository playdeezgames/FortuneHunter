#pragma once
template<typename TCreatureData>
class RoomCell;
template<typename TCreatureData>
class Creature
{
private:
	friend class RoomCell<TCreatureData>;
	RoomCell<TCreatureData>* roomCell;
	TCreatureData creatureData;
public:
	Creature(TCreatureData creatureData) :roomCell(nullptr), creatureData(creatureData) {}
	const RoomCell<TCreatureData>* GetRoomCell() const { return roomCell; }
	RoomCell<TCreatureData>* GetRoomCell() { return roomCell; }
	TCreatureData GetCreatureData() { return creatureData; }
};
