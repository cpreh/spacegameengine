#include <sge/gui/canvas.hpp>
#include <sge/gui/canvas/font_drawer.hpp>
#include <sge/font/font.hpp>
#include <sge/iostream.hpp>

void sge::gui::canvas::object::draw_text(
		font::metrics_ptr const metrics,
		color const c,
		string const &text,
		point const &pos,
		dim const &max_size,
		font::align_h::type const h,
		font::align_v::type const v,
		font::flag_t const f)
{
	font::font(
		metrics,
		font::drawer_ptr(new font_drawer(view_,c))).draw_text(
			text,
			pos,
			max_size,
			h,
			v,
			f);
}
