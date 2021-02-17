#include "HelpPage.h"
const std::string PROPERTY_NEXT_PAGE = "nextPage";
const std::string PROPERTY_PREVIOUS_PAGE = "previousPage";
const std::string PROPERTY_LABELS = "labels";

const std::string PROPERTY_X = "x";
const std::string PROPERTY_Y = "y";
const std::string PROPERTY_TEXT = "text";
const std::string PROPERTY_COLOR = "color";
const std::string PROPERTY_DROP_SHADOW = "dropShadow";

HelpPage::HelpPage(const nlohmann::json& properties, const tggd::common::SpriteFont& font)
	: nextPage(properties[PROPERTY_NEXT_PAGE])
	, previousPage(properties[PROPERTY_PREVIOUS_PAGE])
	, labels()
{
	auto& entries = properties[PROPERTY_LABELS];
	for (auto& entry : entries)
	{
		bool hasDropShadow = false;
		tggd::common::XY<int> dropShadowOffset(0,0);
		std::string dropShadowColor = "";
		if (entry.count(PROPERTY_DROP_SHADOW) > 0)
		{
			auto& dropShadow = entry[PROPERTY_DROP_SHADOW];
			hasDropShadow = true;
			dropShadowOffset = { (int)dropShadow[PROPERTY_X], (int)dropShadow[PROPERTY_Y] };
			dropShadowColor = dropShadow[PROPERTY_COLOR];
		}
		labels.push_back
		(
			tggd::common::Label
			(
				tggd::common::XY<int>(entry[PROPERTY_X], entry[PROPERTY_Y]),
				entry[PROPERTY_TEXT],
				font,
				entry[PROPERTY_COLOR],
				hasDropShadow,
				dropShadowOffset,
				dropShadowColor
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
