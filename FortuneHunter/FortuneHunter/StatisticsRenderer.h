#pragma once
#include "BaseMenuRenderer.h"
#include "Statistics.h"
class StatisticsRenderer : public BaseMenuRenderer
{
private:
	const Statistics& statistics;
public:
	StatisticsRenderer
	(
		SDL_Renderer*, 
		const tggd::common::SpriteFont&, 
		const tggd::common::Sprite*,
		const Statistics&
	);
	void Draw() const;
};
