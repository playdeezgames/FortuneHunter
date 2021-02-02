#include "ControllerManager.h"
namespace tggd::common
{
	ControllerManager::ControllerManager(FinishManager& finishManager)
	{
		finishManager.Add(this);
	}


	void ControllerManager::Start()
	{
		for (int index = 0; index < SDL_NumJoysticks(); ++index)
		{
			SDL_GameController* controller = SDL_GameControllerOpen(index);
			if (controller)
			{
				controllers[index] = controller;
			}
			else
			{
				SDL_Joystick* stick = SDL_JoystickOpen(index);
				if (stick)
				{
					joysticks[index] = stick;
				}
			}
		}
	}

	void ControllerManager::Finish()
	{
		for (auto& entry : joysticks)
		{
			if (entry.second)
			{
				SDL_JoystickClose(entry.second);
				entry.second = nullptr;
			}
		}
		joysticks.clear();

		for (auto& entry : controllers)
		{
			if (entry.second)
			{
				SDL_GameControllerClose(entry.second);
				entry.second = nullptr;
			}
		}
		controllers.clear();

	}

	bool ControllerManager::IsController(int which) const
	{
		return controllers.contains(which);
	}

}
