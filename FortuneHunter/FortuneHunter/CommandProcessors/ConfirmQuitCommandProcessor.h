#pragma once
#include "..\Common\CommandProcessor.h"
#include "..\Game\Command.h"
#include "..\Game\GameState.h"
#include "..\Game\ConfirmState.h"
class ConfirmQuitCommandProcessor : public tggd::common::CommandProcessor<Command>
{
private:
	GameState& gameState;
	ConfirmState& confirmState;
public:
	ConfirmQuitCommandProcessor(GameState&, ConfirmState&);
	void OnCommand(const Command&);
};