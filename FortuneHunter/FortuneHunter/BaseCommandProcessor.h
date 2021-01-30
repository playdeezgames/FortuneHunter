#pragma once
#include "CommandProcessor.h"
#include "Command.h"
#include "UIState.h"
class BaseCommandProcessor : public tggd::common::CommandProcessor<Command>
{
private:
	UIState& uiState;
protected:
	void SetUIState(UIState);
public:
	BaseCommandProcessor(UIState&);
};
