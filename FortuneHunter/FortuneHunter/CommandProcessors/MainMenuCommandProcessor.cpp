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
	}
}

MainMenuCommandProcessor::MainMenuCommandProcessor(GameState& gameState, MainMenuState& mainMenuState)
	: mainMenuState(mainMenuState)
	, gameState(gameState)
{

}