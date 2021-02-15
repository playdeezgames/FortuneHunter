#pragma once
#include "BaseRenderer.h"
#include "Sprite.h"
class BaseMenuRenderer : public BaseRenderer
{
private:
	const tggd::common::Sprite* background;
public:
	BaseMenuRenderer
	(
		SDL_Renderer*, 
		const tggd::common::SpriteFont&, 
		const tggd::common::Sprite*
	);
	void Draw() const;
};

