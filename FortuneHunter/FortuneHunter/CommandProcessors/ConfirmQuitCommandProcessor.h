#pragma once
#include "..\Common\Interfaces\CommandProcessor.h"
#include "Command.h"
#include "..\UI\UIState.h"
#include "..\UI\ConfirmState.h"
class ConfirmQuitCommandProcessor : public tggd::common::CommandProcessor<Command>
{
private:
	UIState& uiState;//TODO: put into base command processor
	ConfirmState& confirmState;
public:
	ConfirmQuitCommandProcessor(UIState&, ConfirmState&);
	void OnCommand(const Command&);
};