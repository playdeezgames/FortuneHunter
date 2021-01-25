#pragma once
#include "BaseCommandProcessor.h"
#include "..\UI\MainMenuState.h"
#include "..\UI\UIState.h"
#include "Command.h"
#include "..\Game\GameData.h"
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

