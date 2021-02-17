#pragma once
#include "XY.h"
#include <string>
#include "SpriteFont.h"
#include "json.hpp"
namespace tggd::common
{
	class Label
	{
	private:
		tggd::common::XY<int> xy;
		std::string text;
		const tggd::common::SpriteFont& font;
		std::string color;
		bool hasDropShadow;
		tggd::common::XY<int> dropShadowXY;
		std::string dropShadowColor;
	public:
		Label
		(
			const tggd::common::XY<int>&,
			const std::string&,
			const tggd::common::SpriteFont&,
			const std::string&,
			bool,
			const tggd::common::XY<int>&,
			const std::string&
		);
		Label(const nlohmann::json&);
		void Draw(SDL_Renderer*) const;
	};
}
