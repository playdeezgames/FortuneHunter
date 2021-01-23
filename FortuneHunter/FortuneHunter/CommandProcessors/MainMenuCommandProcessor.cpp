#include "MainMenuCommandProcessor.h"
void MainMenuCommandProcessor::OnCommand(const Command& command)
{
	switch (command)
	{
	case Command::UP:
		mainMenuState = PreviousMainMenuState(mainMenuState);
		break;
	case Command::DOWN:
		mainMenuState = NextMainMenuState(mainMenuState);
		break;
	case Command::GREEN:
		DoGreenAction();
		break;
	}
}

MainMenuCommandProcessor::MainMenuCommandProcessor
	(
		UIState& uiState, 
		MainMenuState& mainMenuState,
		GameData& gameData
	)
	: mainMenuState(mainMenuState)
	, uiState(uiState)
	, gameData(gameData)
{

}

void MainMenuCommandProcessor::DoGreenAction()
{
	switch (mainMenuState)
	{
	case MainMenuState::QUIT:
		uiState = UIState::CONFIRM_QUIT;
		return;
	case MainMenuState::START:
		uiState = UIState::IN_PLAY;
		return;
	}
}
