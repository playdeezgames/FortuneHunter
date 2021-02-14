#include "OptionsRenderer.h"
#include "ColorConstants.h"
#include "OptionsConstants.h"
#include <sstream>

OptionsRenderer::OptionsRenderer
(
	SDL_Renderer* renderer,
	const tggd::common::SpriteFont& romFont,
	const tggd::common::Sprite* background,
	const tggd::common::SoundManager& soundManager,
	const OptionsState& optionsState
)
	: BaseMenuRenderer(renderer, romFont, background)
	, soundManager(soundManager)
	, optionsState(optionsState)
{

}

void OptionsRenderer::DrawOptionsItem(int line, const std::string& text, const OptionsState& state) const
{
	GetRomFont().WriteText
	(
		GetMainRenderer(),
		tggd::common::XY<int>(Constants::UI::Options::MENU_OFFSET_X + Constants::UI::DROP_SHADOW_X,
			Constants::UI::Options::MENU_OFFSET_Y + Constants::UI::Options::LINE_HEIGHT * line + Constants::UI::DROP_SHADOW_Y),
		text,
		Constants::Color::BLACK
	);
	GetRomFont().WriteText
	(
		GetMainRenderer(),
		tggd::common::XY<int>(Constants::UI::Options::MENU_OFFSET_X,
		Constants::UI::Options::MENU_OFFSET_Y + Constants::UI::Options::LINE_HEIGHT * line),
		text,
		(optionsState == state) ? (Constants::Color::YELLOW) : (Constants::Color::WHITE)
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
	BaseMenuRenderer::Draw();
	GetRomFont().WriteText
	(
		GetMainRenderer(), 
		tggd::common::XY<int>
		(
			Constants::UI::Options::TITLE_OFFSET_X + Constants::UI::DROP_SHADOW_X, 
			Constants::UI::Options::TITLE_OFFSET_Y + Constants::UI::DROP_SHADOW_Y
		), 
		Constants::UI::Options::TITLE, 
		Constants::Color::BLACK
	);
	GetRomFont().WriteText(GetMainRenderer(), tggd::common::XY<int>(Constants::UI::Options::TITLE_OFFSET_X, Constants::UI::Options::TITLE_OFFSET_Y), Constants::UI::Options::TITLE, Constants::Color::LIGHT_GREEN);
	//TODO: split vvv into three functions!
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
