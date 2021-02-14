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
#include "ItemDescriptorManager.h"
#include "Creature.h"
#include "Item.h"
#include "HunterDescriptorManager.h"
class GameData
{
private:
	const tggd::common::SoundManager& soundManager;
	const CreatureDescriptorManager& creatureDescriptors;
	const HunterDescriptorManager& hunterDescriptors;
	const ItemDescriptorManager& itemDescriptors;
	tggd::common::Room<TerrainType, ObjectType, RoomCellFlags> room;
	Hunter* hunter;
	int difficulty;

	void ClearHunter();
	void PlaceHunter();

	void UpdateRoom();
	Hunter* GetHunter();
	void ClearLights();
	void LightAndExploreAroundHunter();
	void AttackCreature(Creature*);
	void DamageCreature(Creature*, int);
	void ResolveAttacksOnHunter(const std::vector<tggd::common::RoomCell<TerrainType, ObjectType, RoomCellFlags>*>&);
	bool InteractWithCellObject(tggd::common::RoomCellObject<TerrainType, ObjectType, RoomCellFlags>*);
	void AttemptToEnterCell(tggd::common::RoomCell<TerrainType, ObjectType, RoomCellFlags>*, tggd::common::RoomCell<TerrainType, ObjectType, RoomCellFlags>*);
	bool AttemptToPickUpItem(Item*);
	void DoBomb();
	std::vector<tggd::common::RoomCell<TerrainType, ObjectType, RoomCellFlags>*> DetermineAdjacentCells(tggd::common::RoomCell<TerrainType, ObjectType, RoomCellFlags>*);
public:
	GameData
	(
		const tggd::common::SoundManager&, 
		const CreatureDescriptorManager&,
		const ItemDescriptorManager&,
		const HunterDescriptorManager&
	);
	~GameData();
	const Hunter* GetHunter() const;
	bool CanContinue() const;
	const tggd::common::Room<TerrainType, ObjectType, RoomCellFlags>& GetRoom() const;
	tggd::common::Room<TerrainType, ObjectType, RoomCellFlags>& GetRoom();
	void Start();
	size_t GetMoves() const;
	void MoveHunter(RoomDirection);
	void UseBomb();
	int GetScore() const;
	void SetDifficulty(int);
	int GetDifficulty() const;
};
