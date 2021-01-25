#include "InPlayCommandProcessor.h"
InPlayCommandProcessor::InPlayCommandProcessor(UIState& uiState, GameData& gameData)
	: uiState(uiState)
	, gameData(gameData)
{

}
void InPlayCommandProcessor::OnCommand(const Command& command)
{
	switch (command)
	{
	case Command::BACK:
		uiState = UIState::MAIN_MENU;
		return;
	case Command::UP:
		MoveHunter(RoomDirection::NORTH);
		return;
	case Command::DOWN:
		MoveHunter(RoomDirection::SOUTH);
		return;
	case Command::LEFT:
		MoveHunter(RoomDirection::WEST);
		return;
	case Command::RIGHT:
		MoveHunter(RoomDirection::EAST);
		return;
	}
}

void InPlayCommandProcessor::MoveHunter(RoomDirection direction)
{
	Creature* hunter = gameData.GetHunter();
	RoomCell* cell = hunter->GetRoomCell();
	int column = (int)cell->GetColumn();
	int row = (int)cell->GetRow();
	int nextColumn = RoomDirectionHelper::GetNextColumn(column, row, direction);
	int nextRow = RoomDirectionHelper::GetNextRow(column, row, direction);
	RoomCell* nextCell = gameData.GetRoom().GetCell(nextColumn, nextRow);
	if(nextCell->GetTerrain()==Terrain::FLOOR)
	{
		cell->SetCreature(nullptr);
		nextCell->SetCreature(hunter);
	}
}
