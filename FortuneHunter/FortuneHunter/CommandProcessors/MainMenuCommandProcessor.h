#pragma once
#include "..\Common\CommandProcessor.h"
#include "..\Game\MainMenuState.h"
#include "..\Game\GameState.h"
#include "..\Game\Command.h"
class MainMenuCommandProcessor : public tggd::common::CommandProcessor<Command>
{
private:
	GameState& gameState;//TODO: put into base command processor
	MainMenuState& mainMenuState;
	void DoGreenAction();
public:
	MainMenuCommandProcessor(GameState&, MainMenuState&);
	void OnCommand(const Command&);
};
