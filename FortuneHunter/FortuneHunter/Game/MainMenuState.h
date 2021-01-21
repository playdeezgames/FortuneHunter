#pragma once
enum class MainMenuState
{
	START,
	QUIT
};
MainMenuState NextMainMenuState(const MainMenuState&);
MainMenuState PreviousMainMenuState(const MainMenuState&);
