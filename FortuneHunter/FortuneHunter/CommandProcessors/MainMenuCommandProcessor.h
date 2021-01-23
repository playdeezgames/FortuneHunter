#pragma once
#include "..\Common\Interfaces\CommandProcessor.h"
#include "..\Game\MainMenuState.h"
#include "..\Game\UIState.h"
#include "Command.h"
class MainMenuCommandProcessor : public tggd::common::CommandProcessor<Command>
{
private:
	UIState& uiState;//TODO: put into base command processor
	MainMenuState& mainMenuState;
	void DoGreenAction();
public:
	MainMenuCommandProcessor(UIState&, MainMenuState&);
	void OnCommand(const Command&);
};

