#pragma once
#include "BaseDescriptorManager.h"
#include "HelpPage.h"
#include <string>
class HelpPageManager: public tggd::common::BaseDescriptorManager<std::string, HelpPage>
{
private:
	const tggd::common::SpriteFont& font;
protected:
	std::string ParseKey(const std::string&);
	HelpPage* ParseDescriptor(const nlohmann::json&);
public:
	HelpPageManager(tggd::common::FinishManager&, const tggd::common::SpriteFont&);
};