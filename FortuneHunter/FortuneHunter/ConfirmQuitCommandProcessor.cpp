#include "ConfirmQuitCommandProcessor.h"
void ConfirmQuitCommandProcessor::OnCommand(const Command& command)
{
	switch (command)
	{
	case Command::UP:
	case Command::DOWN:
		confirmState = (confirmState==ConfirmState::YES) ? (ConfirmState::NO) : (ConfirmState::YES);
		return;
	case Command::BACK:
		SetUIState(UIState::MAIN_MENU);
		return;
	case Command::GREEN:
		switch (confirmState)
		{
		case ConfirmState::YES:
			SetUIState(UIState::QUIT);
			return;
		case ConfirmState::NO:
			SetUIState(UIState::MAIN_MENU);
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
	: BaseCommandProcessor(uiState)
	, confirmState(confirmState)
{

}