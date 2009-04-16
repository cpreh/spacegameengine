#include <sge/gui/canvas/object.hpp>
#include <sge/assert.hpp>
#include <sge/math/rect_util.hpp>
#include <sge/renderer/fill_pixels.hpp>
#include <sge/renderer/subimage_view.hpp>
#include <sge/lexical_cast.hpp>

void sge::gui::canvas::object::draw_rect(
	rect const &r,
	color const c,
	rect_type::type const t)
{
	SGE_ASSERT_MESSAGE(
		math::contains(area(),r),
		SGE_TEXT("tried to draw rectangle ")+
			lexical_cast<string>(r)+
			SGE_TEXT(" which is not completely inside ")+
			lexical_cast<string>(area()));

	switch (t)
	{
		case rect_type::solid:
			renderer::fill_pixels(
				renderer::subimage_view(
					view_,
					math::structure_cast<renderer::lock_rect>(r)),
				c);
		break;
		case rect_type::outline:
		{
			point_container ps;
			ps.push_back(point(r.left(),r.top()));
			ps.push_back(point(r.left(),r.bottom()));
			ps.push_back(point(r.right(),r.bottom()));
			ps.push_back(point(r.right(),r.top()));
			draw_line_strip(
				ps,
				c,
				line_type::solid,
				strip_type::closed);
		}
		break;
	}
}
