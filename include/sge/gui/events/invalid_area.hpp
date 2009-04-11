#ifndef SGE_GUI_EVENTS_INVALID_AREA_HPP_INCLUDED
#define SGE_GUI_EVENTS_INVALID_AREA_HPP_INCLUDED

#include <sge/gui/image_view.hpp>
#include <sge/gui/rect.hpp>
#include <sge/gui/export.hpp>
#include <sge/math/rect_impl.hpp>

namespace sge
{
namespace gui
{
namespace events
{
class invalid_area
{
public:
	SGE_GUI_SYMBOL invalid_area(
		image_view const &,
		rect const &);
	SGE_GUI_SYMBOL image_view const &texture() const;
	SGE_GUI_SYMBOL rect const area() const;
private:
	// image view
	image_view texture_;
	// the (absolute) area which is invalid
	rect const area_;
};
}
}
}

#endif
