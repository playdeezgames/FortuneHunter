#include "StatisticsCommandProcessor.h"
StatisticsCommandProcessor::StatisticsCommandProcessor(UIState& state)
	:BaseCommandProcessor(state)
{

}

void StatisticsCommandProcessor::OnCommand(const Command& command)
{
	switch (command)
	{
	case Command::RED:
	case Command::GREEN:
	case Command::BACK:
		SetUIState(UIState::MAIN_MENU);
		return;
	}
}
