#pragma once
#include "BaseMenuRenderer.h"
#include <vector>
#include <string>
#include "Label.h"
#include "HelpPageManager.h"
class InstructionsRenderer : public BaseMenuRenderer
{
private:
	const HelpPageManager& helpPages;
	const std::string& currentPage;
public:
	InstructionsRenderer
	(
		SDL_Renderer*, 
		const tggd::common::SpriteFont&, 
		const tggd::common::Sprite*, 
		const HelpPageManager&,
		const std::string&
	);
	void Draw() const;
};
