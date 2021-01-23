#pragma once
#include "..\Common\Interfaces\CommandProcessor.h"
#include "..\UI\MainMenuState.h"
#include "..\UI\UIState.h"
#include "Command.h"
#include "..\Game\GameData.h"
class MainMenuCommandProcessor : public tggd::common::CommandProcessor<Command>
{
private:
	GameData& gameData;
	UIState& uiState;//TODO: put into base command processor
	MainMenuState& mainMenuState;
	void DoGreenAction();
public:
	MainMenuCommandProcessor(UIState&, MainMenuState&, GameData&);
	void OnCommand(const Command&);
};

