#include "InstructionsCommandProcessor.h"

InstructionsCommandProcessor::InstructionsCommandProcessor(UIState& uiState)
	: BaseCommandProcessor(uiState)
{

}

void InstructionsCommandProcessor::OnCommand(const Command& command)
{
	switch (command)
	{
	case Command::GREEN:
	case Command::RED:
	case Command::BACK:
	case Command::START:
		SetUIState(UIState::MAIN_MENU);
		break;
	}
}
