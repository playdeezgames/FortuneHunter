#include "AboutCommandProcessor.h"

AboutCommandProcessor::AboutCommandProcessor(UIState& uiState)
	: BaseCommandProcessor(uiState)
{

}

void AboutCommandProcessor::OnCommand(const Command& command)
{
	switch (command)
	{
	case Command::GREEN:
	case Command::BACK:
	case Command::START:
		SetUIState(UIState::MAIN_MENU);
		break;
	}
}
