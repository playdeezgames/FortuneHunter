#pragma once
#include "BaseCommandProcessor.h"
#include "MainMenuState.h"
#include "UIState.h"
#include "Command.h"
#include "GameData.h"
#include "Options.h"
class MainMenuCommandProcessor : public tggd::common::BaseCommandProcessor<Command, UIState>
{
private:
	GameData& gameData;
	MainMenuState& mainMenuState;
	Options& options;
	void DoMenuItemAction();
public:
	MainMenuCommandProcessor(UIState&, MainMenuState&, GameData&, Options&);
	void OnCommand(const Command&);
};

