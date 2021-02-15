#include "ColorManager.h"
namespace tggd::common
{
	std::string ColorManager::ParseKey(const std::string& key)
	{
		return key;
	}

	const std::string PROPERTY_RED = "r";
	const std::string PROPERTY_GREEN = "g";
	const std::string PROPERTY_BLUE = "b";
	const std::string PROPERTY_ALPHA = "a";

	SDL_Color* ColorManager::ParseDescriptor(const nlohmann::json& properties)
	{
		SDL_Color* result = new SDL_Color();
		result->r = (Uint8)properties[PROPERTY_RED];
		result->g = (Uint8)properties[PROPERTY_GREEN];
		result->b = (Uint8)properties[PROPERTY_BLUE];
		result->a = (Uint8)properties[PROPERTY_ALPHA];
		return result;
	}

	ColorManager::ColorManager(tggd::common::FinishManager& finishManager)
		: BaseDescriptorManager(finishManager)
	{

	}
}