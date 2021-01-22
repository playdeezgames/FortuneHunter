#include "ConfirmQuitCommandProcessor.h"
void ConfirmQuitCommandProcessor::OnCommand(const Command& command)
{
	switch (command)
	{
	case Command::UP:
	case Command::DOWN:
		confirmState = (confirmState==ConfirmState::YES) ? (ConfirmState::NO) : (ConfirmState::YES);
		return;
	case Command::GREEN:
		switch (confirmState)
		{
		case ConfirmState::YES:
			gameState = GameState::QUIT;
			return;
		case ConfirmState::NO:
			gameState = GameState::MAIN_MENU;
			return;
		default:
			return;
		}
	}
}

ConfirmQuitCommandProcessor::ConfirmQuitCommandProcessor
	(
		GameState& gameState,
		ConfirmState& confirmState
	)
	: gameState(gameState)
	, confirmState(confirmState)
{

}