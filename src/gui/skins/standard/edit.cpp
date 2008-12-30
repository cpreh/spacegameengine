#include "../../utility/max_dim.hpp"
#include <sge/font/font.hpp>
#include <sge/gui/widgets/edit.hpp>
#include <sge/gui/skins/standard.hpp>

namespace
{
sge::string const string_square(sge::gui::dim const &s)
{
	sge::string const line(
		static_cast<sge::string::size_type>(s.w()),
		SGE_TEXT('W'));
	sge::string result;
	for (sge::gui::unit i = 0; i < s.h(); ++i)
		result += line;
	return result;
}
}

sge::gui::dim const sge::gui::skins::standard::size_hint(
	widgets::edit const &w) const
{
	return math::structure_cast<unit>(
		font::font(w.font()).text_size(
			string_square(w.desired_size()),
			utility::max_dim<font::unit>())
		.size());
}

void sge::gui::skins::standard::draw(
	widgets::edit const &,
	events::invalid_area const &)
{
}
