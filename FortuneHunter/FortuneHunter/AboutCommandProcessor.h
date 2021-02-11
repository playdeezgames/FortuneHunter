#pragma once
#include "BaseCommandProcessor.h"
#include "Command.h"
#include "UIState.h"
class AboutCommandProcessor : public tggd::common::BaseCommandProcessor<Command, UIState>
{
public:
	AboutCommandProcessor(UIState&);
	void OnCommand(const Command&);
};

