#pragma once
#include <map>
#include <SDL.h>
namespace tggd::common
{
	class ControllerManager
	{
	private:
		std::map<int, SDL_Joystick*> joysticks;
		std::map<int, SDL_GameController*> controllers;
	public:
		void Start();
		void Finish();
		bool IsController(int) const;
	};
}
