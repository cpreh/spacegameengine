#include <sge/gui/font_drawer_canvas.hpp>
#include <sge/renderer/scoped_lock.hpp>
#include <sge/iostream.hpp>

sge::gui::font_drawer_canvas::font_drawer_canvas(canvas &canvas_)
	: canvas_(canvas_)
{
}

void sge::gui::font_drawer_canvas::begin_rendering(
	size_type const /*buffer_chars*/,
	font::pos const &/*pos*/,
	font::dim const /*size*/)
{
}

void sge::gui::font_drawer_canvas::draw_char(
	char_type const, 
	font::pos const &p, 
	font::const_image_view const &data)
{
	canvas_.blit_font(
		math::structure_cast<unit>(p),
		data,
		fg_,
		bg_);
}

void sge::gui::font_drawer_canvas::end_rendering()
{
}
