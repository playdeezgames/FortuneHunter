#pragma once
#include "BaseCommandProcessor.h"
#include "MainMenuState.h"
#include "UIState.h"
#include "Command.h"
#include "GameData.h"
class MainMenuCommandProcessor : public BaseCommandProcessor
{
private:
	GameData& gameData;
	MainMenuState& mainMenuState;
	void DoGreenAction();
public:
	MainMenuCommandProcessor(UIState&, MainMenuState&, GameData&);
	void OnCommand(const Command&);
};
