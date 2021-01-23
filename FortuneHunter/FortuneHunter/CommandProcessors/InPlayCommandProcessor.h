#pragma once
#include "..\Common\Interfaces\CommandProcessor.h"
#include "Command.h"
#include "..\UI\UIState.h"
#include "..\Game\GameData.h"
class InPlayCommandProcessor : public tggd::common::CommandProcessor<Command>
{
private:
	UIState& uiState;//TODO: put into base command processor
	GameData& gameData;
public:
	InPlayCommandProcessor(UIState&, GameData&);
	void OnCommand(const Command&);
};