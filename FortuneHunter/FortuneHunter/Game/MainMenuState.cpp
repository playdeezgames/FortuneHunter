#include "MainMenuState.h"
MainMenuState NextMainMenuState(const MainMenuState& state)
{
	switch (state)
	{
	case MainMenuState::START:
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
	case MainMenuState::QUIT:
		return MainMenuState::START;
	}
	throw "nope!";
}
