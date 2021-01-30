#pragma once
enum class MainMenuState
{
	START,
	INSTRUCTIONS,
	ABOUT,
	OPTIONS,
	QUIT
};
MainMenuState NextMainMenuState(const MainMenuState&);
MainMenuState PreviousMainMenuState(const MainMenuState&);
