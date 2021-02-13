#pragma once
#include "BaseCommandProcessor.h"
#include "Command.h"
#include "UIState.h"
#include "GameData.h"
#include "RoomDirection.h"
#include "Statistics.h"
class InPlayCommandProcessor : public tggd::common::BaseCommandProcessor<Command,UIState>
{
private:
	GameData& gameData;
	Statistics& statistics;
	void TransitionToFinalScore();
public:
	InPlayCommandProcessor(UIState&, GameData&, Statistics&);
	void OnCommand(const Command&);
};