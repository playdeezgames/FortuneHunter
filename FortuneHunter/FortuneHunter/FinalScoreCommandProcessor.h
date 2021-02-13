#pragma once
#include "BaseCommandProcessor.h"
#include "Command.h"
#include "UIState.h"
class FinalScoreCommandProcessor : public tggd::common::BaseCommandProcessor<Command, UIState>
{
public:
	FinalScoreCommandProcessor(UIState&);
	void OnCommand(const Command&);
};