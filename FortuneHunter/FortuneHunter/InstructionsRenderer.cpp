#include "InstructionsRenderer.h"
#include "ColorConstants.h"
InstructionsRenderer::InstructionsRenderer
(
	SDL_Renderer* renderer, 
	const tggd::common::SpriteFont& font,
	const tggd::common::Sprite* background,
	const HelpPageManager& helpPages,
	const std::string& currentPage
)
	: BaseMenuRenderer(renderer, font, background)
	, helpPages(helpPages)
	, currentPage(currentPage)
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
