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
	case Command::START:
		DoMenuItemAction();
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

void MainMenuCommandProcessor::DoMenuItemAction()
{
	switch (mainMenuState)
	{
	case MainMenuState::QUIT:
		SetUIState(UIState::CONFIRM_QUIT);
		return;
	case MainMenuState::START:
		if (!gameData.CanContinue())
		{
			gameData.Start();
		}
		SetUIState(UIState::IN_PLAY);
		return;
	case MainMenuState::OPTIONS:
		SetUIState(UIState::OPTIONS);
		return;
	case MainMenuState::ABOUT:
		SetUIState(UIState::ABOUT);
		return;
	case MainMenuState::INSTRUCTIONS:
		SetUIState(UIState::INSTRUCTIONS);
		return;
	}
}
