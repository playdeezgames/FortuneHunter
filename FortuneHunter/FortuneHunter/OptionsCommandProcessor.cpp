#include "OptionsCommandProcessor.h"
OptionsCommandProcessor::OptionsCommandProcessor
(
	UIState& uiState, 
	OptionsState& optionsState, 
	tggd::common::SoundManager& soundManager,
	const Options& options
)
	: BaseCommandProcessor(uiState)
	, optionsState(optionsState)
	, soundManager(soundManager)
	, options(options)
{

}

void OptionsCommandProcessor::OnCommand(const Command& command)
{
	switch (command)
	{
	case Command::UP:
		optionsState = OptionsStateHelper::Previous(optionsState);
		break;
	case Command::DOWN:
		optionsState = OptionsStateHelper::Next(optionsState);
		break;
	case Command::LEFT:
		DoDecrease();
		break;
	case Command::RIGHT:
		DoIncrease();
		break;
	case Command::GREEN:
		DoGreenAction();
		break;
	}
}

void OptionsCommandProcessor::DoIncrease()
{
	switch (optionsState)
	{
	case OptionsState::SFX_VOLUME:
		IncreaseSfxVolume();
		break;
	case OptionsState::MUX_VOLUME:
		IncreaseMuxVolume();
		break;
	}
}

const int VOLUME_DELTA = 16;

void OptionsCommandProcessor::DoDecrease()
{
	switch (optionsState)
	{
	case OptionsState::SFX_VOLUME:
		DecreaseSfxVolume();
		break;
	case OptionsState::MUX_VOLUME:
		DecreaseMuxVolume();
		break;
	}
}

void OptionsCommandProcessor::DoGreenAction()
{
	switch (optionsState)
	{
	case OptionsState::TOGGLE_MUTE:
		ToggleMute();
		break;
	case OptionsState::BACK:
		SetUIState(UIState::MAIN_MENU);
		break;
	}
}

void OptionsCommandProcessor::IncreaseSfxVolume()
{
	soundManager.SetSfxVolume(soundManager.GetSfxVolume() + VOLUME_DELTA);
	options.Save();
}

void OptionsCommandProcessor::IncreaseMuxVolume()
{
	soundManager.SetMuxVolume(soundManager.GetMuxVolume() + VOLUME_DELTA);
	options.Save();

}

void OptionsCommandProcessor::DecreaseSfxVolume()
{
	soundManager.SetSfxVolume(soundManager.GetSfxVolume() - VOLUME_DELTA);
	options.Save();
}

void OptionsCommandProcessor::DecreaseMuxVolume()
{
	soundManager.SetMuxVolume(soundManager.GetMuxVolume() - VOLUME_DELTA);
	options.Save();
}

void OptionsCommandProcessor::ToggleMute()
{
	soundManager.SetMuted(!soundManager.IsMuted());
	options.Save();
}
