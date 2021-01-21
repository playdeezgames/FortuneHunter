#pragma once
#include "..\Common\Renderer.h"
#include "..\Common\SpriteManager.h"
class MainMenuRenderer : public tggd::common::Renderer
{
private:
	SDL_Renderer* renderer;
	const tggd::common::SpriteManager& spriteManager;
protected:
	SDL_Renderer* GetMainRenderer() const;
public:
	MainMenuRenderer(SDL_Renderer*, const tggd::common::SpriteManager&);
	void Draw() const;
};

