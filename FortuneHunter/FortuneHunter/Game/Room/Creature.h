#pragma once
template<typename TTerrain, typename TCreatureData>
class RoomCell;
template<typename TTerrain, typename TCreatureData>
class Creature
{
private:
	friend class RoomCell<TTerrain, TCreatureData>;
	RoomCell<TTerrain, TCreatureData>* roomCell;
	TCreatureData creatureData;
public:
	Creature(TCreatureData creatureData) :roomCell(nullptr), creatureData(creatureData) {}
	const RoomCell<TTerrain, TCreatureData>* GetRoomCell() const { return roomCell; }
	RoomCell<TTerrain, TCreatureData>* GetRoomCell() { return roomCell; }
	TCreatureData GetCreatureData() { return creatureData; }
};
