#pragma once
#include "BaseCommandProcessor.h"
#include "Command.h"
#include "UIState.h"
class StatisticsCommandProcessor : public tggd::common::BaseCommandProcessor<Command, UIState>
{
public:
	StatisticsCommandProcessor(UIState&);
	void OnCommand(const Command&);
};