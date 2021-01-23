#pragma once
#include "..\Common\Interfaces\CommandProcessor.h"
#include "Command.h"
#include "..\Game\GameState.h"
#include "..\Game\ConfirmState.h"
class ConfirmQuitCommandProcessor : public tggd::common::CommandProcessor<Command>
{
private:
	GameState& gameState;//TODO: put into base command processor
	ConfirmState& confirmState;
public:
	ConfirmQuitCommandProcessor(GameState&, ConfirmState&);
	void OnCommand(const Command&);
};