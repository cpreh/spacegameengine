#include <sge/gui/impl/style/text_color.hpp>
#include <sge/image/color/predef.hpp>
#include <sge/image/color/any/object.hpp>


sge::image::color::any::object
sge::gui::impl::style::text_color()
{
	return
		sge::image::color::predef::black();
}
