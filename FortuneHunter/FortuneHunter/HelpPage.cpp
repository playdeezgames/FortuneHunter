#include "HelpPage.h"
const std::string PROPERTY_NEXT_PAGE = "nextPage";
const std::string PROPERTY_PREVIOUS_PAGE = "previousPage";
const std::string PROPERTY_LABELS = "labels";

const std::string PROPERTY_X = "x";
const std::string PROPERTY_Y = "y";
const std::string PROPERTY_TEXT = "text";
const std::string PROPERTY_COLOR = "color";

HelpPage::HelpPage(const nlohmann::json& properties, const tggd::common::SpriteFont& font)
	: nextPage(properties[PROPERTY_NEXT_PAGE])
	, previousPage(properties[PROPERTY_PREVIOUS_PAGE])
	, labels()
{
	auto& entries = properties[PROPERTY_LABELS];
	for (auto& entry : entries)
	{
		labels.push_back
		(
			tggd::common::Label
			(
				tggd::common::XY<int>(entry[PROPERTY_X], entry[PROPERTY_Y]),
				entry[PROPERTY_TEXT],
				font,
				entry[PROPERTY_COLOR]
			)
		);
	}
}

const std::string& HelpPage::GetNextPage() const
{
	return nextPage;
}

const std::string& HelpPage::GetPreviousPage() const
{
	return previousPage;
}

const std::vector< tggd::common::Label>& HelpPage::GetLabels() const
{
	return labels;
}
