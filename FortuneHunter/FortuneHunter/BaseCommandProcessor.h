#pragma once
#include "CommandProcessor.h"
namespace tggd::common
{
	template<typename TCommand, typename TState>
	class BaseCommandProcessor : public tggd::common::CommandProcessor<TCommand>
	{
	private:
		TState& uiState;
	protected:
		void SetUIState(TState state)
		{
			uiState = state;
		}
	public:
		BaseCommandProcessor(TState& uiState)
			: uiState(uiState)
		{

		}
	};
}
