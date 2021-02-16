#include "MainMenuState.h"

static MainMenuState nextStates[] =
{
	MainMenuState::DIFFICULTY,
	MainMenuState::INSTRUCTIONS,
	MainMenuState::STATISTICS,
	MainMenuState::ABOUT,
	MainMenuState::OPTIONS,
	MainMenuState::QUIT,
	MainMenuState::START
};

MainMenuState MainMenuStateHelper::Next(MainMenuState state)
{
	return nextStates[(int)state];
}

static MainMenuState previousStates[] =
{
	MainMenuState::QUIT,
	MainMenuState::START,
	MainMenuState::DIFFICULTY,
	MainMenuState::INSTRUCTIONS,
	MainMenuState::STATISTICS,
	MainMenuState::ABOUT,
	MainMenuState::OPTIONS
};

MainMenuState MainMenuStateHelper::Previous(MainMenuState state)
{
	return previousStates[(int)state];
}
