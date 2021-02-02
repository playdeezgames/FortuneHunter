#pragma once
#include "Renderer.h"
#include <map>
#include "FinishManager.h"
namespace tggd::common
{
	template<typename TIdentifier>
	class RenderManager 
		: public Renderer
		, public Finisher
	{
	private:
		std::map<TIdentifier, Renderer*> renderers;
		const TIdentifier& current;
	protected:
		SDL_Renderer* GetMainRenderer() const { return nullptr; }
	public:
		RenderManager
		(
			const TIdentifier& current,
			FinishManager& finishManager
		)
			: current(current)
			, renderers()
		{
			finishManager.Add(this);
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

