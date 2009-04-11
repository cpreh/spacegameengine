#include <sge/gui/events/invalid_area.hpp>

sge::gui::events::invalid_area::invalid_area(
	image_view const &texture_,
	rect const &area_)
:
	texture_(texture_),
	area_(area_)
{}

sge::gui::image_view const &
sge::gui::events::invalid_area::texture() const
{
	return texture_;
}

sge::gui::rect const
sge::gui::events::invalid_area::area() const
{
	return area_;
}
