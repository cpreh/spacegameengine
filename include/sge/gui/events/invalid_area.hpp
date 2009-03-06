#ifndef SGE_GUI_EVENTS_INVALID_AREA_HPP_INCLUDED
#define SGE_GUI_EVENTS_INVALID_AREA_HPP_INCLUDED

#include <sge/gui/types.hpp>
#include <sge/renderer/image_view.hpp>
#include <sge/export.hpp>

namespace sge
{
namespace gui
{
namespace events
{
class invalid_area
{
	public:
	SGE_SYMBOL invalid_area(
		renderer::image_view const &,
		rect const &);
	renderer::image_view const &texture() const { return texture_; }
	rect const area() const { return area_; }
	private:
	// image view
	renderer::image_view texture_;
	// the (absolute) area which is invalid
	rect const area_;
};
}
}
}

#endif
