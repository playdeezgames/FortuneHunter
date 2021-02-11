#pragma once
#include "BaseCommandProcessor.h"
#include "Command.h"
#include "UIState.h"
#include "ConfirmState.h"
class ConfirmQuitCommandProcessor : public tggd::common::BaseCommandProcessor<Command, UIState>
{
private:
	ConfirmState& confirmState;
public:
	ConfirmQuitCommandProcessor(UIState&, ConfirmState&);
	void OnCommand(const Command&);
};