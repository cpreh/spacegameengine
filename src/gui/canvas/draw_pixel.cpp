#include <sge/gui/canvas.hpp>
#include <sge/assert.hpp>
#include <sge/math/rect_util.hpp>
#include <sge/math/vector/output.hpp>
#include <sge/text.hpp>
#include <sge/renderer/fill_pixels.hpp>
#include <sge/renderer/subimage_view.hpp>
#include <boost/lexical_cast.hpp>

void sge::gui::canvas::object::draw_pixel(
	point const &p,
	color const c)
{
	SGE_ASSERT_MESSAGE(
		math::contains(area(),p),
		SGE_TEXT("tried to draw pixel ")+
		boost::lexical_cast<string>(p)+
		SGE_TEXT(" which is not inside rect ")+
		boost::lexical_cast<string>(area()));
	
	renderer::fill_pixels(
		renderer::subimage_view(
			view_,
			math::structure_cast<renderer::lock_rect>(
				rect(
					p,
					dim(1,1)))),
		c);
}
