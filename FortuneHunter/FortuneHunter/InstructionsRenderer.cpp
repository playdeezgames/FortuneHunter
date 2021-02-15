#include "InstructionsRenderer.h"
#include "ColorConstants.h"
InstructionsRenderer::InstructionsRenderer
(
	SDL_Renderer* renderer, 
	const tggd::common::SpriteFont& font,
	const tggd::common::Sprite* background
)
	: BaseMenuRenderer(renderer, font, background)
	, labels()
{
	labels.push_back(tggd::common::Label(tggd::common::XY<int>(4, 4), "Instructions", font, Constants::Color::DARK_GRAY));
	labels.push_back(tggd::common::Label(tggd::common::XY<int>(0, 0), "Instructions", font, Constants::Color::LIGHT_GREEN));
	labels.push_back(tggd::common::Label(tggd::common::XY<int>(4, 36), "TODO: put some information here!", font, Constants::Color::DARK_GRAY));
	labels.push_back(tggd::common::Label(tggd::common::XY<int>(0, 32), "TODO: put some information here!", font, Constants::Color::WHITE));
}

void InstructionsRenderer::Draw() const
{
	BaseMenuRenderer::Draw();
	for (auto& label : labels)
	{
		label.Draw(GetRenderer());
	}
}
