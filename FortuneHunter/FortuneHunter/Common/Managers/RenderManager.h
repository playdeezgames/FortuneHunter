#pragma once
#include "..\Interfaces\Renderer.h"
#include <map>
namespace tggd::common
{
	template<typename TIdentifier>
	class RenderManager : Renderer
	{
	private:
		std::map<TIdentifier, Renderer*> renderers;
		const TIdentifier& current;
	protected:
		SDL_Renderer* GetMainRenderer() const { return nullptr; }
	public:
		RenderManager(const TIdentifier& current)
			: current(current)
			, renderers()
		{

		}

		void Finish()
		{
			for (auto& entry : renderers)
			{
				if (entry.second)
				{
					delete entry.second;
					entry.second = nullptr;
				}
			}
			renderers.clear();
		}

		void Draw() const
		{
			auto iter = renderers.find(current);
			if (iter != renderers.end())
			{
				iter->second->Draw();
			}
		}

		void AddRenderer(const TIdentifier& identifier, Renderer* renderer)
		{
			renderers[identifier] = renderer;
		}
	};
}

