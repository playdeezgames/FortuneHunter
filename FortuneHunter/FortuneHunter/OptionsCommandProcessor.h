#pragma once
#include "BaseCommandProcessor.h"
#include "Command.h"
#include "UIState.h"
#include "OptionsState.h"
#include "SoundManager.h"
#include "Options.h"
class OptionsCommandProcessor : public tggd::common::BaseCommandProcessor<Command, UIState>
{
private:
	OptionsState& optionsState;
	tggd::common::SoundManager& soundManager;
	const Options& options;
	void DoIncrease();
	void DoDecrease();
	void DoGreenAction();
	void IncreaseSfxVolume();
	void IncreaseMuxVolume();
	void DecreaseSfxVolume();
	void DecreaseMuxVolume();
	void ToggleMute();
public:
	OptionsCommandProcessor(UIState&, OptionsState&, tggd::common::SoundManager&, const Options&);
	void OnCommand(const Command&);
};