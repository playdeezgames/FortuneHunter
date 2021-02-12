#include "OptionsRenderer.h"
#include "ColorConstants.h"
#include "OptionsConstants.h"
#include <sstream>

OptionsRenderer::OptionsRenderer
(
	SDL_Renderer* renderer,
	const tggd::common::SpriteFont& romFont,
	const tggd::common::SoundManager& soundManager,
	const OptionsState& optionsState
)
	: BaseRenderer(renderer, romFont)
	, soundManager(soundManager)
	, optionsState(optionsState)
{

}

void OptionsRenderer::DrawOptionsItem(int line, const std::string& text, const OptionsState& state) const
{
	GetRomFont().WriteText
	(
		GetMainRenderer(),
		tggd::common::XY<int>(0,
		Constants::UI::Options::OFFSET_Y + Constants::UI::Options::LINE_HEIGHT * line),
		text,
		(optionsState == state) ? (Constants::Color::LIGHT_BLUE) : (Constants::Color::GRAY)
	);

}

const std::string VOLUME_FORMAT_PREFIX = "(";
const std::string VOLUME_FORMAT_SUFFIX = "%)";
const int MAXIMUM_PERCENT = 100;

std::string OptionsRenderer::FormatVolume(int volume)
{
	int percent = volume * MAXIMUM_PERCENT / SDL_MIX_MAXVOLUME;
	std::stringstream ss;
	ss << VOLUME_FORMAT_PREFIX << percent << VOLUME_FORMAT_SUFFIX;
	return ss.str();
}


void OptionsRenderer::Draw() const
{
	GetRomFont().WriteText(GetMainRenderer(), tggd::common::XY<int>(0, 0), Constants::UI::Options::TITLE, Constants::Color::GREEN);
	if (soundManager.IsMuted())
	{
		DrawOptionsItem(0, Constants::UI::Options::OPTION_MUTE_ON, OptionsState::TOGGLE_MUTE);
	}
	else
	{
		DrawOptionsItem(0, Constants::UI::Options::OPTION_MUTE_OFF, OptionsState::TOGGLE_MUTE);
	}
	std::stringstream ss;
	ss << Constants::UI::Options::OPTION_SFX_VOLUME << FormatVolume(soundManager.GetSfxVolume());
	DrawOptionsItem(1, ss.str(), OptionsState::SFX_VOLUME);
	ss.str("");
	ss << Constants::UI::Options::OPTION_MUX_VOLUME << FormatVolume(soundManager.GetMuxVolume());
	DrawOptionsItem(2, ss.str(), OptionsState::MUX_VOLUME);
	DrawOptionsItem(3, Constants::UI::Options::OPTION_BACK, OptionsState::BACK);
}
