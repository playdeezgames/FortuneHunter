#include "InPlayCommandProcessor.h"
InPlayCommandProcessor::InPlayCommandProcessor(UIState& uiState, GameData& gameData)
	: BaseCommandProcessor(uiState)
	, gameData(gameData)
{

}
void InPlayCommandProcessor::OnCommand(const Command& command)
{
	switch (command)
	{
	case Command::BACK:
		if (gameData.CanContinue())
		{
			SetUIState(UIState::MAIN_MENU);
		}
		else
		{
			SetUIState(UIState::FINAL_SCORE);
		}
		return;
	case Command::UP:
		gameData.MoveHunter(RoomDirection::NORTH);
		return;
	case Command::DOWN:
		gameData.MoveHunter(RoomDirection::SOUTH);
		return;
	case Command::LEFT:
		gameData.MoveHunter(RoomDirection::WEST);
		return;
	case Command::RIGHT:
		gameData.MoveHunter(RoomDirection::EAST);
		return;
	case Command::GREEN:
		if (gameData.CanContinue())
		{
			gameData.UseBomb();
		}
		else
		{
			SetUIState(UIState::FINAL_SCORE);
		}
		return;
	}
}

