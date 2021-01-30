#include "Application.h"
#include "SDL.h"
#include "SDL_mixer.h"
namespace tggd::common
{
	const int MIXER_FREQUENCY = 44100;
	const int CHANNEL_COUNT = 2;
	const int CHUNK_SIZE = 1024;

	Application* Application::s_application = nullptr;

	Application::Application(int width, int height, const std::string& title)
		: window(nullptr)
		, renderer(nullptr)
		, windowWidth(width)
		, windowHeight(height)
		, windowTitle(title)
	{
		if (!s_application)
		{
			s_application = this;
		}
	}

	void Application::DoStart()
	{
		SDL_Init(SDL_INIT_EVERYTHING);
		Mix_Init(MIX_INIT_OGG);
		Mix_OpenAudio(MIXER_FREQUENCY, MIX_DEFAULT_FORMAT, CHANNEL_COUNT, CHUNK_SIZE);
		SDL_CreateWindowAndRenderer(
			s_application->windowWidth,
			s_application->windowHeight,
			0,
			&s_application->window,
			&s_application->renderer);
		SDL_SetWindowTitle(s_application->window, s_application->windowTitle.c_str());
		s_application->Start();
	}

	void Application::DoPump()
	{
		int oldCounter = SDL_GetTicks();
		int frameCounter;
		SDL_Event evt;
		while(s_application->IsRunning())
		{
			frameCounter = SDL_GetTicks();
			s_application->Update(frameCounter - oldCounter);
			oldCounter = frameCounter;
			s_application->Draw();
			SDL_RenderPresent(s_application->renderer);
			if (SDL_PollEvent(&evt))
			{
				s_application->OnEvent(evt);
			}
		}

	}

	void Application::DoFinish()
	{
		s_application->Finish();
		if (s_application->renderer)
		{
			SDL_DestroyRenderer(s_application->renderer);
			s_application->renderer = nullptr;
		}
		if (s_application->window)
		{
			SDL_DestroyWindow(s_application->window);
			s_application->window = nullptr;
		}
		Mix_CloseAudio();
		Mix_Quit();
		SDL_Quit();
	}


	int Application::Run(const std::vector<std::string>& arguments)
	{
		if (s_application)
		{
			DoStart();
			DoPump();
			DoFinish();
		}
		return 0;
	}
}
