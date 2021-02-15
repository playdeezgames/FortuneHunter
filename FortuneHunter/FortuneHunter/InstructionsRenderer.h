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
	std::string currentPage;
public:
	InstructionsRenderer
	(
		SDL_Renderer*, 
		const tggd::common::SpriteFont&, 
		const tggd::common::Sprite*, 
		const HelpPageManager&
	);
	void Draw() const;
};
