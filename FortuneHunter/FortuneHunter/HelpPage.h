#pragma once
#include "json.hpp"
#include "Label.h"
#include <string>
#include <vector>
class HelpPage
{
private:
	std::string nextPage;
	std::string previousPage;
	std::vector<tggd::common::Label> labels;
public:
	HelpPage(const nlohmann::json&, const tggd::common::SpriteFont&);
	const std::string& GetNextPage() const;
	const std::string& GetPreviousPage() const;
	const std::vector< tggd::common::Label>& GetLabels() const;
};
