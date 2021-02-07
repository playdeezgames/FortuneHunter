#include "MainMenuCommandProcessor.h"
void MainMenuCommandProcessor::OnCommand(const Command& command)
{
	switch (command)
	{
	case Command::UP:
		mainMenuState = MainMenuStateHelper::Previous(mainMenuState);
		break;
	case Command::DOWN:
		mainMenuState = MainMenuStateHelper::Next(mainMenuState);
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
	: BaseCommandProcessor(uiState)
	, mainMenuState(mainMenuState)
	, gameData(gameData)
{

}

void MainMenuCommandProcessor::DoGreenAction()
{
	switch (mainMenuState)
	{
	case MainMenuState::QUIT:
		SetUIState(UIState::CONFIRM_QUIT);
		return;
	case MainMenuState::START:
		gameData.Start();
		SetUIState(UIState::IN_PLAY);
		return;
	case MainMenuState::OPTIONS:
		SetUIState(UIState::OPTIONS);
		return;
	}
}
