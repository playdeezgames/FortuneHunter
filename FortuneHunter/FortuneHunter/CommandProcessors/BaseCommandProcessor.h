#pragma once
#include "..\Common\Interfaces\CommandProcessor.h"
#include "Command.h"
#include "..\UI\UIState.h"
class BaseCommandProcessor : public tggd::common::CommandProcessor<Command>
{
private:
	UIState& uiState;
protected:
	void SetUIState(UIState);
public:
	BaseCommandProcessor(UIState&);
};
