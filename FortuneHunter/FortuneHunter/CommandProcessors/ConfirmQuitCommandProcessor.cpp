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
			uiState = UIState::QUIT;
			return;
		case ConfirmState::NO:
			uiState = UIState::MAIN_MENU;
			return;
		default:
			return;
		}
	}
}

ConfirmQuitCommandProcessor::ConfirmQuitCommandProcessor
	(
		UIState& uiState,
		ConfirmState& confirmState
	)
	: uiState(uiState)
	, confirmState(confirmState)
{

}