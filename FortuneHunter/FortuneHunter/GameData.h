#pragma once
#include "Room.h"
#include "RoomDirection.h"
#include "TerrainType.h"
#include "ObjectType.h"
#include "RoomCellFlags.h"
#include "Maze.h"
#include "RoomGenerator.h"
#include "Hunter.h"
#include "SoundManager.h"
#include "CreatureDescriptorManager.h"
class GameData
{
private:
	const tggd::common::SoundManager& soundManager;
	const CreatureDescriptorManager& creatureDescriptors;
	tggd::common::Room<TerrainType, ObjectType, RoomCellFlags> room;
	Hunter* hunter;

	void ClearHunter();
	void PlaceHunter();

	void UpdateRoom();
	Hunter* GetHunter();
	void ClearLights();
	void LightAndExploreAroundHunter();
	void AcquireKey();
	void AttemptToOpenDoor(tggd::common::RoomCellObject<TerrainType, ObjectType, RoomCellFlags>*);
	void AttackCreature(tggd::common::RoomCellObject<TerrainType, ObjectType, RoomCellFlags>*);
	bool InteractWithCellObject(tggd::common::RoomCellObject<TerrainType, ObjectType, RoomCellFlags>*);
	void AttemptToEnterCell(tggd::common::RoomCell<TerrainType, ObjectType, RoomCellFlags>*, tggd::common::RoomCell<TerrainType, ObjectType, RoomCellFlags>*);
	std::vector<tggd::common::RoomCell<TerrainType, ObjectType, RoomCellFlags>*> DetermineAdjacentCells(tggd::common::RoomCell<TerrainType, ObjectType, RoomCellFlags>*);
public:
	GameData(const tggd::common::SoundManager&, const CreatureDescriptorManager&);
	~GameData();
	const Hunter* GetHunter() const;
	const tggd::common::Room<TerrainType, ObjectType, RoomCellFlags>& GetRoom() const;
	tggd::common::Room<TerrainType, ObjectType, RoomCellFlags>& GetRoom();
	void Start();
	size_t GetMoves() const;
	void MoveHunter(RoomDirection);
};
