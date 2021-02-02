#pragma once
#include <set>
#include "Finisher.h"
namespace tggd::common
{
	class FinishManager
	{
	private:
		std::set<Finisher*> finishers;
	public:
		void Add(Finisher*);
		void Finish();
	};
}

