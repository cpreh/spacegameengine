#include <sge/gui/impl/style/border_color.hpp>
#include <sge/image/color/predef.hpp>
#include <sge/image/color/any/object.hpp>


sge::image::color::any::object
sge::gui::impl::style::border_color()
{
	return
		sge::image::color::predef::black();
}
