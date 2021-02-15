#include "HelpPageManager.h"
std::string HelpPageManager::ParseKey(const std::string& key)
{
	return key;
}

HelpPage* HelpPageManager::ParseDescriptor(const nlohmann::json& properties)
{
	return new HelpPage(properties, font);
}

HelpPageManager::HelpPageManager
(
	tggd::common::FinishManager& finishManager, 
	const tggd::common::SpriteFont& font
)
	: BaseDescriptorManager(finishManager)
	, font(font)
{

}
