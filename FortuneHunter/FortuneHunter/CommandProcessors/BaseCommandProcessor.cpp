#include "BaseCommandProcessor.h"
void BaseCommandProcessor::SetUIState(UIState state)
{
	uiState = state;
}

BaseCommandProcessor::BaseCommandProcessor(UIState& uiState)
	: uiState(uiState)
{
}
