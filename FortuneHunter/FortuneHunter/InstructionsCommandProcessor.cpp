#include "InstructionsCommandProcessor.h"

InstructionsCommandProcessor::InstructionsCommandProcessor
(
	UIState& uiState,
	const HelpPageManager& helpPages,
	std::string& currentPage
)
	: BaseCommandProcessor(uiState)
	, helpPages(helpPages)
	, currentPage(currentPage)
{

}

void InstructionsCommandProcessor::NextHelpPage()
{
	currentPage = helpPages.GetDescriptor(currentPage)->GetNextPage();
}

void InstructionsCommandProcessor::PreviousHelpPage()
{
	currentPage = helpPages.GetDescriptor(currentPage)->GetPreviousPage();
}


void InstructionsCommandProcessor::OnCommand(const Command& command)
{
	switch (command)
	{
	case Command::GREEN:
	case Command::BACK:
	case Command::START:
		SetUIState(UIState::MAIN_MENU);
		return;
	case Command::NEXT:
	case Command::RIGHT:
		NextHelpPage();
		return;
	case Command::PREVIOUS:
	case Command::LEFT:
		PreviousHelpPage();
		return;
	}
}
