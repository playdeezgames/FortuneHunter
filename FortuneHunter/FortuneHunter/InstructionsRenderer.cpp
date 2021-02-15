#include "InstructionsRenderer.h"
#include "ColorConstants.h"
InstructionsRenderer::InstructionsRenderer
(
	SDL_Renderer* renderer, 
	const tggd::common::SpriteFont& font,
	const tggd::common::Sprite* background,
	const HelpPageManager& helpPages
)
	: BaseMenuRenderer(renderer, font, background)
	, helpPages(helpPages)
	, currentPage("first") //TODO: magic string
{
}

void InstructionsRenderer::Draw() const
{
	BaseMenuRenderer::Draw();
	auto helpPage = helpPages.GetDescriptor(currentPage);
	for (auto& label : helpPage->GetLabels())
	{
		label.Draw(GetRenderer());
	}
}
