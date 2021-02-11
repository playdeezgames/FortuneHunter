#pragma once
#include "BaseCommandProcessor.h"
#include "Command.h"
#include "UIState.h"
class InstructionsCommandProcessor : public tggd::common::BaseCommandProcessor<Command, UIState>
{
public:
	InstructionsCommandProcessor(UIState&);
	void OnCommand(const Command&);
};

