#pragma once
#include <SDL.h>
#include <string>
#include <vector>
#include "Renderer.h"
#include "Updater.h"
#include "EventHandler.h"
namespace tggd::common
{
	class Application : public Renderer, public Updater, public EventHandler
	{
	private:
		Application() = delete;
		Application(const Application&) = delete;
		Application(Application&&) = delete;

		SDL_Window* window;
		std::string windowTitle;
		int windowWidth;
		int windowHeight;
		
		SDL_Renderer* renderer;

		static Application* s_application;
		static void DoStart();
		static void DoPump();
		static void DoFinish();
	protected:
		SDL_Renderer* GetMainRenderer() const { return renderer; }
		virtual void Start() = 0;
		virtual void Finish() = 0;
	public:
		Application(int, int, const std::string&);
		static int Run(const std::vector<std::string>&);
	};
}


