#pragma once
#include "BaseRenderer.h"
#include "OptionsState.h"
#include "SoundManager.h"
class OptionsRenderer : public BaseRenderer
{
private:
	const OptionsState& optionsState;
	const tggd::common::SoundManager& soundManager;	
	void DrawOptionsItem(int, const std::string&, const OptionsState&) const;
public:
	OptionsRenderer
	(
		SDL_Renderer*, 
		const tggd::common::SpriteFont&, 
		const tggd::common::SoundManager&,
		const OptionsState&);
	void Draw() const;
};

