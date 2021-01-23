#pragma once
#include "..\Common\Interfaces\CommandProcessor.h"
#include "..\UI\MainMenuState.h"
#include "..\UI\UIState.h"
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

