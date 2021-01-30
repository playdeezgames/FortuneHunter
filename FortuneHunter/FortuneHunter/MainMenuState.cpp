#include "MainMenuState.h"
MainMenuState NextMainMenuState(const MainMenuState& state)
{
	switch (state)
	{
	case MainMenuState::START:
		return MainMenuState::INSTRUCTIONS;
	case MainMenuState::INSTRUCTIONS:
		return MainMenuState::ABOUT;
	case MainMenuState::ABOUT:
		return MainMenuState::OPTIONS;
	case MainMenuState::OPTIONS:
		return MainMenuState::QUIT;
	case MainMenuState::QUIT:
		return MainMenuState::START;
	}
	throw "nope!";
}

MainMenuState PreviousMainMenuState(const MainMenuState& state)
{
	switch (state)
	{
	case MainMenuState::START:
		return MainMenuState::QUIT;
	case MainMenuState::INSTRUCTIONS:
		return MainMenuState::START;
	case MainMenuState::ABOUT:
		return MainMenuState::INSTRUCTIONS;
	case MainMenuState::OPTIONS:
		return MainMenuState::ABOUT;
	case MainMenuState::QUIT:
		return MainMenuState::OPTIONS;
	}
	throw "nope!";
}
