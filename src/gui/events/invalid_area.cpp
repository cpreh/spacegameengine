#include <sge/gui/events/invalid_area.hpp>

sge::gui::events::invalid_area::invalid_area(
	image_view const &texture_,
	rect const &area_)
:
	texture_(texture_),
	area_(area_)
{}
