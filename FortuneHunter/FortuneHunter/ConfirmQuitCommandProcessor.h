#pragma once
#include "BaseCommandProcessor.h"
#include "Command.h"
#include "UIState.h"
#include "ConfirmState.h"
class ConfirmQuitCommandProcessor : public BaseCommandProcessor
{
private:
	ConfirmState& confirmState;
public:
	ConfirmQuitCommandProcessor(UIState&, ConfirmState&);
	void OnCommand(const Command&);
};