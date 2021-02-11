#pragma once
#include "BaseCommandProcessor.h"
#include "MainMenuState.h"
#include "UIState.h"
#include "Command.h"
#include "GameData.h"
class MainMenuCommandProcessor : public tggd::common::BaseCommandProcessor<Command, UIState>
{
private:
	GameData& gameData;
	MainMenuState& mainMenuState;
	void DoMenuItemAction();
public:
	MainMenuCommandProcessor(UIState&, MainMenuState&, GameData&);
	void OnCommand(const Command&);
};

