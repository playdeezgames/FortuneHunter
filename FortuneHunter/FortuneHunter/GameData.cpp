#include "GameData.h"
#include "RoomConstants.h"
#include "Maze.h"
#include "Utility.h"
#include "SoundsConstants.h"
#include "Creature.h"
#include "SimpleObject.h"
#include "Item.h"
GameData::GameData
(
	const tggd::common::SoundManager& soundManager,
	const CreatureDescriptorManager& creatureDescriptors,
	const ItemDescriptorManager& itemDescriptors
)
	: room(Constants::Room::COLUMNS, Constants::Room::ROWS, TerrainType::FLOOR)
	, soundManager(soundManager)
	, hunter(nullptr)
	, creatureDescriptors(creatureDescriptors)
	, itemDescriptors(itemDescriptors)
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
	hunter = new Hunter();
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

void GameData::AttemptToOpenDoor(tggd::common::RoomCellObject<TerrainType, ObjectType, RoomCellFlags>* object)
{
		if (hunter->HasKey())
		{
			soundManager.PlaySound(Constants::Sounds::UNLOCK);
			hunter->RemoveKey();
			object->GetRoomCell()->RemoveObject();
		}
		else
		{
			soundManager.PlaySound(Constants::Sounds::DOOR_LOCKED);
		}
}

void GameData::AttackCreature(tggd::common::RoomCellObject<TerrainType, ObjectType, RoomCellFlags>* object)
{
	Creature* creature = dynamic_cast<Creature*>(object);
	if (creature)
	{
		creature->AddWounds(hunter->GetAttackStrength());
		//TODO: play "hit" or "death" sounds for creature
		if (creature->IsDead())
		{
			auto creatureCell = creature->GetRoomCell();
			auto drop = creature->GetDrop();
			creatureCell->RemoveObject();
			creatureCell->SetObject(drop);
		}
	}
}

bool GameData::AttemptToPickUpItem(tggd::common::RoomCellObject<TerrainType, ObjectType, RoomCellFlags>* object)
{
	Item* item = dynamic_cast<Item*>(object);
	bool result = true;
	if (item)
	{
		auto itemType = item->GetDescriptor()->GetItemType();
		if (hunter->CanPickUp(itemType))
		{
			hunter->PickUp(itemType);
			soundManager.PlaySound(item->GetDescriptor()->GetPickUpSfx());
			result = !item->GetDescriptor()->DoesStopMovement();
			item->GetRoomCell()->RemoveObject();//leave on bottom, because deletes item!
		}
		else
		{
			//TODO: sound effect for not picking up the item
		}
	}
	return result;
}


bool GameData::InteractWithCellObject(tggd::common::RoomCellObject<TerrainType, ObjectType, RoomCellFlags>* object)
{
	//TODO: attempt to dynamic cast to creature and item instead of a switch!
	switch (object->GetData())
	{
	case ObjectType::ZOMBIE:
		AttackCreature(object);
		return false;
	case ObjectType::EXIT_KEY:
	case ObjectType::EXIT:
	case ObjectType::DOOR_EW:
	case ObjectType::DOOR_NS:
	case ObjectType::KEY:
	case ObjectType::DIAMOND:
	case ObjectType::POTION:
	case ObjectType::SHIELD:
		return AttemptToPickUpItem(object);
	default:
		return false;
	}
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

void GameData::MoveHunter(RoomDirection direction)
{
	Hunter* hunter = GetHunter();
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
	for (auto adjacentCell : adjacentCells)//TODO: this loop goes into its own function
	{
		if (adjacentCell != hunter->GetRoomCell() && adjacentCell->GetObject())
		{
			Creature* creature = dynamic_cast<Creature*>(adjacentCell->GetObject());
			if (creature)
			{
				hunter->AddWounds(creature->GetAttackStrength());
				//TODO: sound for hunter hit or dead!
			}
		}
	}
	hunter->IncrementMoves();
	UpdateRoom();
}