#pragma once
#include "BaseCommandProcessor.h"
#include "Command.h"
#include "UIState.h"
#include "GameData.h"
#include "RoomDirection.h"
class InPlayCommandProcessor : public tggd::common::BaseCommandProcessor<Command,UIState>
{
private:
	GameData& gameData;
public:
	InPlayCommandProcessor(UIState&, GameData&);
	void OnCommand(const Command&);
};