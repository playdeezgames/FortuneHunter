#pragma once
#include "Renderer.h"
#include <map>
#include "FinishManager.h"
#include "Utility.h"
namespace tggd::common
{
	template<typename TIdentifier>
	class RenderManager 
		: public Finisher
	{
	private:
		std::map<TIdentifier, Renderer*> renderers;
		const TIdentifier& current;
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
					tggd::common::Utility::SafeDelete(entry.second);
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

