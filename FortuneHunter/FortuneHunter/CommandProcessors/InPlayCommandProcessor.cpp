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
	}
}
