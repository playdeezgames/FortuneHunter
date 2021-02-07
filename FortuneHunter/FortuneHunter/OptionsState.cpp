#include "OptionsState.h"

static OptionsState nextStates[] =
{
	OptionsState::SFX_VOLUME,
	OptionsState::MUX_VOLUME,
	OptionsState::BACK,
	OptionsState::TOGGLE_MUTE
};

OptionsState OptionsStateHelper::Next(OptionsState current)
{
	return nextStates[(int)current];
}

static OptionsState previousStates[] =
{
	OptionsState::BACK,
	OptionsState::TOGGLE_MUTE,
	OptionsState::SFX_VOLUME,
	OptionsState::MUX_VOLUME
};

OptionsState OptionsStateHelper::Previous(OptionsState current)
{
	return previousStates[(int)current];

}
