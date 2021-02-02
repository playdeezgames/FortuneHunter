#pragma once
#include <map>
#include <SDL.h>
#include "FinishManager.h"
namespace tggd::common
{
	class ControllerManager: public Finisher
	{
	private:
		std::map<int, SDL_Joystick*> joysticks;
		std::map<int, SDL_GameController*> controllers;
	public:
		ControllerManager(FinishManager&);
		void Start();
		void Finish();
		bool IsController(int) const;
	};
}
