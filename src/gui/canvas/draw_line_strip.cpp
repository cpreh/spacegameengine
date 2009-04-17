#include <sge/gui/canvas/object.hpp>
#include <sge/math/vector/basic_impl.hpp>
#include <sge/assert.hpp>

void sge::gui::canvas::object::draw_line_strip(
	point_container const &points,
	color const c,
	line_type::type const lt,
	strip_type::type const st)
{
	SGE_ASSERT(points.size() > 1);

	for (point_container::size_type i = 0;
		i < static_cast<point_container::size_type>(points.size()-1);
		++i)
		draw_line(points[i],points[i+1],c,lt);

	switch (st)
	{
		case strip_type::open:
		break;
		case strip_type::closed:
			draw_line(points[points.size()-1],points[0],c,lt);
		break;
	}
}
