#pragma once
#include "BaseDescriptorManager.h"
#include <string>
#include <SDL.h>
namespace tggd::common
{
	class ColorManager : public BaseDescriptorManager<std::string, SDL_Color>
	{
	protected:
		std::string ParseKey(const std::string&);
		SDL_Color* ParseDescriptor(const nlohmann::json&);
	public:
		ColorManager(tggd::common::FinishManager&);
	};
}