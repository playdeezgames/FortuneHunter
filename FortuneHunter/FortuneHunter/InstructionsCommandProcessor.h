#pragma once
#include "BaseCommandProcessor.h"
#include "Command.h"
#include "UIState.h"
#include <string>
#include "HelpPageManager.h"
class InstructionsCommandProcessor : public tggd::common::BaseCommandProcessor<Command, UIState>
{
private:
	std::string& currentPage;
	const HelpPageManager& helpPages;
	void NextHelpPage();
	void PreviousHelpPage();
public:
	InstructionsCommandProcessor
	(
		UIState&,
		const HelpPageManager&,
		std::string&
	);
	void OnCommand(const Command&);
};

