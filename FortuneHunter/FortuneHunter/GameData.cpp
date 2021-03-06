#include "GameData.h"
#include "RoomConstants.h"
#include "SoundsConstants.h"
GameData::GameData
(
	const tggd::common::SoundManager& soundManager,
	const CreatureDescriptorManager& creatureDescriptors,
	const ItemDescriptorManager& itemDescriptors,
	const HunterDescriptorManager& hunterDescriptors
)
	: room(Constants::Room::COLUMNS, Constants::Room::ROWS, TerrainType::FLOOR)
	, soundManager(soundManager)
	, hunter(nullptr)
	, creatureDescriptors(creatureDescriptors)
	, itemDescriptors(itemDescriptors)
	, hunterDescriptors(hunterDescriptors)
	, difficulty(0)
{
}

size_t GameData::GetMoves() const
{
	return hunter->GetMoves();
}

void GameData::ClearHunter()
{
	if (hunter)
	{
		if (hunter->GetRoomCell())
		{
			hunter->GetRoomCell()->SetObject(nullptr);
		}
		tggd::common::Utility::SafeDelete(hunter);
	}
}

GameData::~GameData()
{
	ClearHunter();
}

const tggd::common::Room<TerrainType, ObjectType, RoomCellFlags>& GameData::GetRoom() const
{
	return room;
}

tggd::common::Room<TerrainType, ObjectType, RoomCellFlags>& GameData::GetRoom()
{
	return room;
}

const Hunter* GameData::GetHunter() const
{
	return hunter;
}

Hunter* GameData::GetHunter()
{
	return hunter;
}

void GameData::PlaceHunter()
{
	hunter = new Hunter(hunterDescriptors.GetDescriptor(GetDifficulty()));
	while (hunter->GetRoomCell() == nullptr)
	{
		int column = tggd::common::Utility::GenerateRandomNumberFromRange(0, Constants::Room::COLUMNS);
		int row = tggd::common::Utility::GenerateRandomNumberFromRange(0, Constants::Room::ROWS);
		auto roomCell = room.GetCell(column, row);
		if (roomCell->GetTerrain() == TerrainType::FLOOR && !roomCell->HasObject())
		{
			roomCell->SetObject(hunter);
		}
	}
}

void GameData::Start()
{
	ClearHunter();
	RoomGenerator generator(room, creatureDescriptors, itemDescriptors);
	generator.GenerateRoom();
	PlaceHunter();
	UpdateRoom();
}

void GameData::ClearLights()
{
	for (size_t column = 0; column < room.GetColumns(); ++column)
	{
		for (size_t row = 0; row < room.GetRows(); ++row)
		{
			room.GetCell(column, row)->ClearFlag(RoomCellFlags::LIT);
		}
	}
}

void GameData::LightAndExploreAroundHunter()
{
	if (hunter && hunter->GetRoomCell())
	{
		int roomColumn = (int)hunter->GetRoomCell()->GetColumn();
		int roomRow = (int)hunter->GetRoomCell()->GetRow();
		for (int column = roomColumn - 1; column <= roomColumn + 1; ++column)
		{
			for (int row = roomRow - 1; row <= roomRow + 1; ++row)
			{
				auto cell = room.GetCell(column, row);
				if (cell)
				{
					cell->SetFlag(RoomCellFlags::LIT);
					cell->SetFlag(RoomCellFlags::EXPLORED);
				}
			}
		}
	}
}

void GameData::UpdateRoom()
{
	ClearLights();
	LightAndExploreAroundHunter();
}

void GameData::DamageCreature(Creature* creature, int damage)
{
	if (creature)
	{
		creature->AddWounds(damage);
		if (creature->IsDead())
		{
			soundManager.PlaySound(creature->GetDescriptor()->GetDeathSfx());
			auto creatureCell = creature->GetRoomCell();
			auto drop = creature->GetDrop();
			creatureCell->RemoveObject();
			creatureCell->SetObject(drop);
		}
		else
		{
			soundManager.PlaySound(creature->GetDescriptor()->GetDamageSfx());
		}
	}

}


void GameData::AttackCreature(Creature* creature)
{
	DamageCreature(creature, hunter->GetAttackStrength());
}

const size_t MAXIMUM_SPAWN_ATTEMPTS = 50;

void GameData::SpawnItems(ItemType itemType, size_t count)
{
	size_t attempts = 0;
	auto descriptor = itemDescriptors.GetDescriptor(itemType);
	while (count > 0 && attempts < MAXIMUM_SPAWN_ATTEMPTS)
	{
		attempts++;
		size_t column = (size_t)tggd::common::Utility::GenerateRandomNumberFromRange(0, room.GetColumns());
		size_t row = (size_t)tggd::common::Utility::GenerateRandomNumberFromRange(0, room.GetRows());
		auto cell = room.GetCell(column, row);
		if (!cell->HasObject() && descriptor->CanSpawnOnTerrain(cell->GetTerrain()))
		{
			cell->SetObject(new Item(descriptor));
			attempts = 0;
			count--;
		}
	}
}


bool GameData::AttemptToPickUpItem(Item* item)
{
	bool result = true;
	if (item)
	{
		auto itemType = item->GetDescriptor()->GetItemType();
		if (hunter->CanPickUp(itemType))
		{
			hunter->PickUp(itemType);
			soundManager.PlaySound(item->GetDescriptor()->GetPickUpSfx());
			result = !item->GetDescriptor()->DoesStopMovement();
			if (item->GetDescriptor()->DoesSpawnItems())
			{
				SpawnItems(item->GetDescriptor()->GetSpawnItemType(), item->GetDescriptor()->GetSpawnItemCount());
			}
			item->GetRoomCell()->RemoveObject();//leave on bottom, because deletes item!
		}
		else
		{
			soundManager.PlaySound(item->GetDescriptor()->GetFailureSfx());
			result = false;
		}
	}
	return result;
}


bool GameData::InteractWithCellObject(tggd::common::RoomCellObject<TerrainType, ObjectType, RoomCellFlags>* object)
{
	//TODO: attempt to dynamic cast to creature and item instead of a switch!
	Creature* creature = dynamic_cast<Creature*>(object);
	if (creature)
	{
		AttackCreature(creature);
		return false;
	}
	Item* item = dynamic_cast<Item*>(object);
	if (item)
	{
		return AttemptToPickUpItem(item);
	}
	return false;
}

void GameData::AttemptToEnterCell(tggd::common::RoomCell<TerrainType, ObjectType, RoomCellFlags>* cell, tggd::common::RoomCell<TerrainType, ObjectType, RoomCellFlags>* nextCell)
{
	bool completeMove = true;
	if (nextCell->HasObject())
	{
		completeMove = InteractWithCellObject(nextCell->GetObject());
	}
	if (completeMove)
	{
		cell->SetObject(nullptr);
		nextCell->SetObject(hunter);
	}
}

std::vector<tggd::common::RoomCell<TerrainType, ObjectType, RoomCellFlags>*> GameData::DetermineAdjacentCells
(
	tggd::common::RoomCell<TerrainType, ObjectType, RoomCellFlags>* startingCell
)
{
	std::vector<tggd::common::RoomCell<TerrainType, ObjectType, RoomCellFlags>*> result;
	if (startingCell)
	{
		auto cellColumn = startingCell->GetColumn();
		auto cellRow = startingCell->GetRow();
		for (auto direction : RoomDirectionHelper::GetAll())
		{
			auto nextColumn = RoomDirectionHelper::GetNextColumn((int)cellColumn, (int)cellRow, direction);
			auto nextRow = RoomDirectionHelper::GetNextRow((int)cellColumn, (int)cellRow, direction);
			auto nextCell = room.GetCell(nextColumn, nextRow);
			if (nextCell)
			{
				result.push_back(nextCell);
			}
		}
	}
	return result;
}

void GameData::ResolveAttacksOnHunter(const std::vector<tggd::common::RoomCell<TerrainType, ObjectType, RoomCellFlags>*>& adjacentCells)
{
	for (auto adjacentCell : adjacentCells)
	{
		if (adjacentCell != hunter->GetRoomCell() && adjacentCell->GetObject())
		{
			Creature* creature = dynamic_cast<Creature*>(adjacentCell->GetObject());
			if (creature)
			{
				hunter->AddWounds(creature->GetAttackStrength());
			}
		}
	}
	//TODO: this should be its own function
	if (hunter->WasHit())
	{
		if (hunter->IsAlive())
		{
			soundManager.PlaySound(hunter->GetDescriptor()->GetDamageSfx());
		}
		else
		{
			soundManager.PlaySound(hunter->GetDescriptor()->GetDeathSfx());
		}
	}
}


void GameData::MoveHunter(RoomDirection direction)
{
	hunter->ClearHit();
	if (hunter && hunter->IsAlive() && !hunter->IsWinner())
	{
		tggd::common::RoomCell<TerrainType, ObjectType, RoomCellFlags>* cell = hunter->GetRoomCell();
		int roomColumn = (int)cell->GetColumn();
		int roomRow = (int)cell->GetRow();
		int nextColumn = RoomDirectionHelper::GetNextColumn(roomColumn, roomRow, direction);
		int nextRow = RoomDirectionHelper::GetNextRow(roomColumn, roomRow, direction);
		tggd::common::RoomCell<TerrainType, ObjectType, RoomCellFlags>* nextCell = GetRoom().GetCell(nextColumn, nextRow);
		auto adjacentCells = DetermineAdjacentCells(cell);
		if (TerrainTypeHelper::IsFloor(nextCell->GetTerrain()))
		{
			AttemptToEnterCell(cell, nextCell);
		}
		else
		{
			soundManager.PlaySound(Constants::Sounds::BUMP_WALL);
		}
		ResolveAttacksOnHunter(adjacentCells);
		hunter->IncrementMoves();
		UpdateRoom();
	}
}

bool GameData::CanContinue() const
{
	return hunter && hunter->IsAlive() && !hunter->IsWinner();
}

void GameData::DoBomb()
{
	for (size_t column = 0; column < room.GetColumns(); ++column)
	{
		for (size_t row = 0; row < room.GetRows(); ++row)
		{
			auto cell = room.GetCell(column, row);
			if (cell->IsFlagSet(RoomCellFlags::LIT))
			{
				Creature* creature = dynamic_cast<Creature*>(cell->GetObject());
				DamageCreature(creature, hunter->GetDescriptor()->GetBombDamage());
			}
		}
	}
}


void GameData::UseBomb()
{
	if (CanContinue())
	{
		if (hunter->UseBomb())
		{
			soundManager.PlaySound(hunter->GetDescriptor()->GetBombSfx());
			DoBomb();
		}
		else
		{
			soundManager.PlaySound(hunter->GetDescriptor()->GetNoBombSfx());
		}
	}
}

int GameData::GetScore() const
{
	return GetHunter()->GetScore();
}

void GameData::SetDifficulty(int value)
{
	difficulty = value;
}

int GameData::GetDifficulty() const
{
	return difficulty;
}

void GameData::NextDifficulty()
{
	difficulty = hunterDescriptors.GetDescriptor(difficulty)->GetNextDifficulty();
}
