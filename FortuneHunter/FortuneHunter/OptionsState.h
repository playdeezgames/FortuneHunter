#pragma once
enum class OptionsState
{
	TOGGLE_MUTE,
	SFX_VOLUME,
	MUX_VOLUME,
	BACK
};
class OptionsStateHelper
{
public:
	static OptionsState Next(OptionsState);
	static OptionsState Previous(OptionsState);
};
