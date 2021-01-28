#include "GameData.h"
#include "..\Constants\Room.h"
#include "Maze\Maze.h"
#include "..\Common\Utility.h"
GameData::GameData()
	: room(Constants::Room::COLUMNS, Constants::Room::ROWS, TerrainType::FLOOR)
	, hunter(nullptr)
	, moves(0)
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


const Room<TerrainType, ObjectType>& GameData::GetRoom() const
{
	return room;
}

Room<TerrainType, ObjectType>& GameData::GetRoom()
{
	return room;
}

const RoomCellObject<TerrainType, ObjectType>* GameData::GetHunter() const
{
	return hunter;
}

RoomCellObject<TerrainType, ObjectType>* GameData::GetHunter()
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
	}
	
	if (mazeCell->HasDoor(MazeDirection::EAST) && mazeCell->GetDoor(MazeDirection::EAST)->IsOpen())
	{
		room.GetCell
		(
			RoomDirectionHelper::GetNextColumn((int)roomColumn, (int)roomRow, RoomDirection::EAST),
			roomRow
		)->SetTerrain(TerrainType::FLOOR);
	}
	if (mazeCell->HasDoor(MazeDirection::SOUTH) && mazeCell->GetDoor(MazeDirection::SOUTH)->IsOpen())
	{
		room.GetCell
		(
			roomColumn, 
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

void GameData::ScaffoldMaze(RoomGenerationContext& context)
{
	ClearRoom();
	Maze maze(Constants::Maze::COLUMNS, Constants::Maze::ROWS);
	maze.Generate();
	ScaffoldMazeCells(maze, context);
}	

int GameData::FlagifyDirection(int column, int row, RoomDirection direction, int flag)
{
	int nextColumn = RoomDirectionHelper::GetNextColumn(column, row, direction);
	int nextRow = RoomDirectionHelper::GetNextRow(column, row, direction);
	auto cell = room.GetCell(nextColumn, nextRow);
	if (!cell || cell->GetTerrain() != TerrainType::FLOOR)
	{
		return flag;
	}
	return 0;
}


void GameData::FlagifyCell(int column, int row)
{
	RoomCell<TerrainType, ObjectType>* cell = room.GetCell(column, row);
	int flags = 0;
	if (cell->GetTerrain() != TerrainType::FLOOR)//TODO: a "need to be flagified" function in a helper?
	{
		flags += FlagifyDirection(column, row, RoomDirection::NORTH, FLAG_NORTH);
		flags += FlagifyDirection(column, row, RoomDirection::EAST, FLAG_EAST);
		flags += FlagifyDirection(column, row, RoomDirection::SOUTH, FLAG_SOUTH);
		flags += FlagifyDirection(column, row, RoomDirection::WEST, FLAG_WEST);
	}
	cell->SetTerrain(flagMap[flags]);
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

void GameData::GenerateRoom()
{
	RoomGenerationContext context;
	ScaffoldMaze(context);
	SmootheTerrain();
}

void GameData::Start()
{
	GenerateRoom();
	hunter = new RoomCellObject<TerrainType, ObjectType>(ObjectType::HUNTER);
	while (hunter->GetRoomCell() == nullptr)//TODO: need a "entry point"
	{
		int column = tggd::common::Utility::GenerateRandomNumberFromRange(0, Constants::Room::COLUMNS);
		int row = tggd::common::Utility::GenerateRandomNumberFromRange(0, Constants::Room::ROWS);
		if (room.GetCell(column, row)->GetTerrain() == TerrainType::FLOOR)
		{
			room.GetCell(column, row)->SetObject(hunter);
		}
	}
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
	RoomCellObject<TerrainType, ObjectType>* hunter = GetHunter();
	RoomCell<TerrainType, ObjectType>* cell = hunter->GetRoomCell();
	int roomColumn = (int)cell->GetColumn();
	int roomRow = (int)cell->GetRow();
	int nextColumn = RoomDirectionHelper::GetNextColumn(roomColumn, roomRow, direction);
	int nextRow = RoomDirectionHelper::GetNextRow(roomColumn, roomRow, direction);
	RoomCell<TerrainType, ObjectType>* nextCell = GetRoom().GetCell(nextColumn, nextRow);
	if (nextCell->GetTerrain() == TerrainType::FLOOR)
	{
		cell->SetObject(nullptr);
		nextCell->SetObject(hunter);
	}
	IncrementMove();
	UpdateRoom();
}

void GameData::PopulateKeysAndLocks()
{

}
