#pragma once
#include "..\Common\Interfaces\CommandProcessor.h"
#include "..\Game\MainMenuState.h"
#include "..\Game\GameState.h"
#include "Command.h"
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

