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
	, moves(0)
	, creatureDescriptors(creatureDescriptors)
{
}

void GameData::IncrementMove()
{
	moves++;
}

size_t GameData::GetMoves() const
{
	return moves;
}


void GameData::ClearHunter()
{
	moves = 0;
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


const tggd::common::Room<TerrainType, ObjectType>& GameData::GetRoom() const
{
	return room;
}

tggd::common::Room<TerrainType, ObjectType>& GameData::GetRoom()
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
		if(mazeCell->HasDoor(direction))
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
	tggd::common::RoomCell<TerrainType, ObjectType>* cell = room.GetCell(column, row);
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
	bool done = false;
	while (!done)
	{
		int column = tggd::common::Utility::GenerateRandomNumberFromRange(0, Constants::Room::COLUMNS);
		int row = tggd::common::Utility::GenerateRandomNumberFromRange(0, Constants::Room::ROWS);
		auto cell = room.GetCell(column, row);
		if (TerrainTypeHelper::IsFloor(cell->GetTerrain()) && !cell->GetObject())
		{
			cell->SetObject(new Creature(descriptor));
			done = true;
		}
	}
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
			room.GetCell(column, row)->SetLit(false);
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
					cell->SetLit(true);
					cell->SetExplored(true);
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

void GameData::MoveHunter(RoomDirection direction)
{
	Hunter* hunter = GetHunter();
	tggd::common::RoomCell<TerrainType, ObjectType>* cell = hunter->GetRoomCell();
	int roomColumn = (int)cell->GetColumn();
	int roomRow = (int)cell->GetRow();
	int nextColumn = RoomDirectionHelper::GetNextColumn(roomColumn, roomRow, direction);
	int nextRow = RoomDirectionHelper::GetNextRow(roomColumn, roomRow, direction);
	tggd::common::RoomCell<TerrainType, ObjectType>* nextCell = GetRoom().GetCell(nextColumn, nextRow);
	if (TerrainTypeHelper::IsFloor(nextCell->GetTerrain()))
	{
		bool completeMove = true;
		if (nextCell->HasObject())
		{
			auto object = nextCell->GetObject();
			switch(object->GetData())
			{
			case ObjectType::KEY:
				soundManager.PlaySound(Constants::Sounds::GET_KEY);
				hunter->AddKey();
				nextCell->RemoveObject();
				break;
			case ObjectType::DOOR_EW:
			case ObjectType::DOOR_NS:
				if (hunter->HasKey())
				{
					soundManager.PlaySound(Constants::Sounds::UNLOCK);
					hunter->RemoveKey();
					nextCell->RemoveObject();
				}
				else
				{
					soundManager.PlaySound(Constants::Sounds::DOOR_LOCKED);
				}
				completeMove = false;
				break;
			default:
				completeMove = false;
			}
		}
		if (completeMove)
		{
			cell->SetObject(nullptr);
			nextCell->SetObject(hunter);
		}
	}
	else
	{
		soundManager.PlaySound(Constants::Sounds::BUMP_WALL);
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
					(direction==RoomDirection::EAST || direction==RoomDirection::WEST) ? 
					(ObjectType::DOOR_NS) : 
					(ObjectType::DOOR_EW);
				tggd::common::RoomCellObject<TerrainType, ObjectType>* object = new tggd::common::SimpleObject<TerrainType, ObjectType>(objectType);
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
			tggd::common::RoomCellObject<TerrainType, ObjectType>* object = new tggd::common::SimpleObject<TerrainType, ObjectType>(ObjectType::KEY);
			roomCell->SetObject(object);
			keyCount--;
		}
	}
}

