#include "GameData.h"
#include "RoomConstants.h"
#include "Maze.h"
#include "Utility.h"
#include "SoundsConstants.h"
#include "Creature.h"
#include "SimpleObject.h"
GameData::GameData
(
	const tggd::common::SoundManager& soundManager,
	const CreatureDescriptorManager& creatureDescriptors
)
	: room(Constants::Room::COLUMNS, Constants::Room::ROWS, TerrainType::FLOOR)
	, soundManager(soundManager)
	, hunter(nullptr)
	, creatureDescriptors(creatureDescriptors)
{
}

void GameData::IncrementMove()
{
	if (hunter)
	{
		hunter->IncrementMoves();
	}
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
		delete hunter;
	}
	hunter = nullptr;
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

void GameData::ClearRoom()
{
	ClearHunter();
	for (int column = 0; column < room.GetColumns(); ++column)
	{
		for (int row = 0; row < room.GetRows(); ++row)
		{
			bool isMazeCell = column % 2 == 1 && row % 2 == 1;
			room.GetCell(column, row)->SetTerrain((isMazeCell) ? (TerrainType::FLOOR) : (TerrainType::WALL_NESW));
		}
	}
}

static TerrainType flagMap[16] =
{
	TerrainType::FLOOR,
	TerrainType::WALL_N,
	TerrainType::WALL_E,
	TerrainType::WALL_NE,
	TerrainType::WALL_S,
	TerrainType::WALL_NS,
	TerrainType::WALL_ES,
	TerrainType::WALL_NES,
	TerrainType::WALL_W,
	TerrainType::WALL_NW,
	TerrainType::WALL_EW,
	TerrainType::WALL_NEW,
	TerrainType::WALL_SW,
	TerrainType::WALL_NSW,
	TerrainType::WALL_ESW,
	TerrainType::WALL_NESW
};
const int FLAG_NORTH = 1;
const int FLAG_EAST = 2;
const int FLAG_SOUTH = 4;
const int FLAG_WEST = 8;

size_t GameData::PlotColumn(size_t column, size_t row)
{
	return column * 2 + 1;
}

size_t GameData::PlotRow(size_t columne, size_t row)
{
	return row * 2 + 1;
}

void GameData::ScaffoldMazeCell(int mazeColumn, int mazeRow, const MazeCell* mazeCell, RoomGenerationContext& context)
{
	size_t roomColumn = PlotColumn(mazeColumn, mazeRow);
	size_t roomRow = PlotRow(mazeColumn, mazeRow);

	if (mazeCell->IsDeadEnd())
	{
		context.AddDeadEnd({ roomColumn, roomRow });
		room.GetCell(roomColumn, roomRow)->SetTerrain(TerrainType::FLOOR_DEAD_END);
	}

	if (mazeCell->HasDoor(MazeDirection::EAST) && mazeCell->GetDoor(MazeDirection::EAST)->IsOpen())
	{
		room.GetCell
		(
			RoomDirectionHelper::GetNextColumn((int)roomColumn, (int)roomRow, RoomDirection::EAST),
			RoomDirectionHelper::GetNextRow((int)roomColumn, (int)roomRow, RoomDirection::EAST)
		)->SetTerrain(TerrainType::FLOOR);
	}
	if (mazeCell->HasDoor(MazeDirection::SOUTH) && mazeCell->GetDoor(MazeDirection::SOUTH)->IsOpen())
	{
		room.GetCell
		(
			RoomDirectionHelper::GetNextColumn((int)roomColumn, (int)roomRow, RoomDirection::SOUTH),
			RoomDirectionHelper::GetNextRow((int)roomColumn, (int)roomRow, RoomDirection::SOUTH)
		)->SetTerrain(TerrainType::FLOOR);
	}
}

void GameData::ScaffoldMazeCells(const Maze& maze, RoomGenerationContext& context)
{
	for (int column = 0; column < maze.GetColumns(); ++column)
	{
		for (int row = 0; row < maze.GetRows(); ++row)
		{
			ScaffoldMazeCell(column, row, maze.GetCell(column, row), context);
		}
	}
}

void GameData::LoopifyMaze(Maze& maze)
{
	size_t counter = Constants::Maze::LOOPIFICATIONS;
	auto directions = MazeDirectionHelper::GetAll();
	while (counter > 0)
	{
		size_t column = (size_t)tggd::common::Utility::GenerateRandomNumberFromRange(0, (int)maze.GetColumns());
		size_t row = (size_t)tggd::common::Utility::GenerateRandomNumberFromRange(0, (int)maze.GetRows());
		MazeDirection direction = directions[tggd::common::Utility::GenerateRandomNumberFromRange(0, (int)directions.size())];
		auto mazeCell = maze.GetCell((int)column, (int)row);
		if (mazeCell->HasDoor(direction))
		{
			auto mazeDoor = mazeCell->GetDoor(direction);
			if (!mazeDoor->IsOpen())
			{
				mazeDoor->SetOpen(true);
				counter--;
			}
		}
	}
}

void GameData::ScaffoldMaze(RoomGenerationContext& context)
{
	ClearRoom();
	Maze maze(Constants::Maze::COLUMNS, Constants::Maze::ROWS);
	maze.Generate();
	LoopifyMaze(maze);
	ScaffoldMazeCells(maze, context);
}

int GameData::FlagifyDirection(int column, int row, RoomDirection direction, int flag)
{
	int nextColumn = RoomDirectionHelper::GetNextColumn(column, row, direction);
	int nextRow = RoomDirectionHelper::GetNextRow(column, row, direction);
	auto cell = room.GetCell(nextColumn, nextRow);
	if (!cell || !TerrainTypeHelper::IsFloor(cell->GetTerrain()))
	{
		return flag;
	}
	return 0;
}


void GameData::FlagifyCell(int column, int row)
{
	tggd::common::RoomCell<TerrainType, ObjectType, RoomCellFlags>* cell = room.GetCell(column, row);
	int flags = 0;
	if (!TerrainTypeHelper::IsFloor(cell->GetTerrain()))//TODO: a "need to be flagified" function in a helper?
	{
		flags += FlagifyDirection(column, row, RoomDirection::NORTH, FLAG_NORTH);
		flags += FlagifyDirection(column, row, RoomDirection::EAST, FLAG_EAST);
		flags += FlagifyDirection(column, row, RoomDirection::SOUTH, FLAG_SOUTH);
		flags += FlagifyDirection(column, row, RoomDirection::WEST, FLAG_WEST);
		cell->SetTerrain(flagMap[flags]);
	}
}

void GameData::SmootheTerrain()
{
	for (int column = 0; column < room.GetColumns(); ++column)
	{
		for (int row = 0; row < room.GetRows(); ++row)
		{
			FlagifyCell(column, row);
		}
	}
}

void GameData::SpawnCreature(const CreatureDescriptor* descriptor)
{
	do
	{
		int column = tggd::common::Utility::GenerateRandomNumberFromRange(0, Constants::Room::COLUMNS);
		int row = tggd::common::Utility::GenerateRandomNumberFromRange(0, Constants::Room::ROWS);
		auto cell = room.GetCell(column, row);
		auto terrainType = cell->GetTerrain();
		if (!descriptor->CanSpawnOnTerrain(terrainType))
		{
			continue;
		}
		auto object = cell->GetObject();
		if (object && !descriptor->CanSpawnOnObject(object->GetData()))
		{
			continue;
		}
		cell->SetObject(new Creature(descriptor, object));
		break;
	} while (true);
}

void GameData::PopulateCreatures()
{
	auto creatureTypes = creatureDescriptors.GetCreatureTypes();
	for (auto creatureType : creatureTypes)
	{
		auto descriptor = creatureDescriptors.GetDescriptor(creatureType);
		auto counter = descriptor->GetNumberAppearing();
		while (counter > 0)
		{
			SpawnCreature(descriptor);
			counter--;
		}
	}
}


void GameData::GenerateRoom()
{
	RoomGenerationContext context;
	ScaffoldMaze(context);
	SmootheTerrain();
	PopulateLocks(context);
	PopulateKeys(context);
	PopulateDeadEnds(context);
	PopulateCreatures();
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
	GenerateRoom();
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

void GameData::AcquireKey()
{
	soundManager.PlaySound(Constants::Sounds::GET_KEY);
	hunter->AddKey();
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

bool GameData::InteractWithCellObject(tggd::common::RoomCellObject<TerrainType, ObjectType, RoomCellFlags>* object)
{
	switch (object->GetData())
	{
	case ObjectType::KEY:
		AcquireKey();
		object->GetRoomCell()->RemoveObject();
		return true;
	case ObjectType::DOOR_EW:
	case ObjectType::DOOR_NS:
		AttemptToOpenDoor(object);
		return false;
	case ObjectType::ZOMBIE:
		AttackCreature(object);
		return false;
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
			auto nextColumn = RoomDirectionHelper::GetNextColumn(cellColumn, cellRow, direction);
			auto nextRow = RoomDirectionHelper::GetNextRow(cellColumn, cellRow, direction);
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
	IncrementMove();
	UpdateRoom();
}

void GameData::PopulateLocks(RoomGenerationContext& context)
{
	for (auto& xy : context.GetDeadEnds())
	{
		size_t roomColumn = xy.GetX();
		size_t roomRow = xy.GetY();
		for (auto direction : RoomDirectionHelper::GetAll())
		{
			size_t nextRoomColumn = RoomDirectionHelper::GetNextColumn((int)roomColumn, (int)roomRow, direction);
			size_t nextRoomRow = RoomDirectionHelper::GetNextRow((int)roomColumn, (int)roomRow, direction);
			auto roomCell = room.GetCell(nextRoomColumn, nextRoomRow);
			if (TerrainTypeHelper::IsFloor(roomCell->GetTerrain()) && !roomCell->HasObject())
			{
				ObjectType objectType =
					(direction == RoomDirection::EAST || direction == RoomDirection::WEST) ?
					(ObjectType::DOOR_NS) :
					(ObjectType::DOOR_EW);
				tggd::common::RoomCellObject<TerrainType, ObjectType, RoomCellFlags>* object = new tggd::common::SimpleObject<TerrainType, ObjectType, RoomCellFlags>(objectType);
				roomCell->SetObject(object);
				break;
			}
		}
	}
}

void GameData::PopulateKeys(RoomGenerationContext& context)
{
	size_t keyCount = context.GetDeadEnds().size();
	while (keyCount > 0)
	{
		size_t roomColumn = tggd::common::Utility::GenerateRandomNumberFromRange(0, (int)room.GetColumns());
		size_t roomRow = tggd::common::Utility::GenerateRandomNumberFromRange(0, (int)room.GetRows());
		auto roomCell = room.GetCell(roomColumn, roomRow);
		if (!roomCell->HasObject() && roomCell->GetTerrain() == TerrainType::FLOOR)
		{
			tggd::common::RoomCellObject<TerrainType, ObjectType, RoomCellFlags>* object = new tggd::common::SimpleObject<TerrainType, ObjectType, RoomCellFlags>(ObjectType::KEY);
			roomCell->SetObject(object);
			keyCount--;
		}
	}
}

void GameData::PopulateDeadEndObject(RoomGenerationContext& context, ObjectType objectType)
{
	do
	{
		size_t index = (size_t)tggd::common::Utility::GenerateRandomNumberFromRange(0, (int)context.GetDeadEnds().size());
		auto& xy = context.GetDeadEnds()[index];
		auto cell = room.GetCell(xy.GetX(), xy.GetY());
		if (cell->GetObject())
		{
			continue;
		}
		cell->SetObject(new tggd::common::SimpleObject<TerrainType, ObjectType, RoomCellFlags>(objectType));
		context.RemoveDeadEndAtIndex(index);
		break;
	} while (true);
}


void GameData::PopulateDeadEnds(RoomGenerationContext& context)
{
	PopulateDeadEndObject(context, ObjectType::EXIT);
	PopulateDeadEndObject(context, ObjectType::EXIT_KEY);
	while (!context.GetDeadEnds().empty())
	{
		PopulateDeadEndObject(context, ObjectType::DIAMOND);
	}
}


