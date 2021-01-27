#pragma once
#include "BaseCommandProcessor.h"
#include "Command.h"
#include "..\UI\UIState.h"
#include "..\Game\GameData.h"
#include "..\Game\Room\RoomDirection.h"
class InPlayCommandProcessor : public BaseCommandProcessor
{
private:
	GameData& gameData;
public:
	InPlayCommandProcessor(UIState&, GameData&);
	void OnCommand(const Command&);
};