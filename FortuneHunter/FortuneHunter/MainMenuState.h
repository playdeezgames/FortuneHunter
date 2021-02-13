#pragma once
enum class MainMenuState
{
	START,
	INSTRUCTIONS,
	STATISTICS,
	ABOUT,
	OPTIONS,
	QUIT
};
class MainMenuStateHelper
{
public:
	static MainMenuState Next(MainMenuState);
	static MainMenuState Previous(MainMenuState);
};
