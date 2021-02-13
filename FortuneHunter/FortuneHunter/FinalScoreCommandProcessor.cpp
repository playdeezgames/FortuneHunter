#include "FinalScoreCommandProcessor.h"
FinalScoreCommandProcessor::FinalScoreCommandProcessor(UIState& state)
	:BaseCommandProcessor(state)
{

}

void FinalScoreCommandProcessor::OnCommand(const Command& command)
{
	switch (command)
	{
	case Command::GREEN:
	case Command::START:
		SetUIState(UIState::MAIN_MENU);
		return;
	}
}
