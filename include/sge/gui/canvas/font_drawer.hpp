#ifndef SGE_GUI_CANVAS_FONT_DRAWER_HPP_INCLUDED
#define SGE_GUI_CANVAS_FONT_DRAWER_HPP_INCLUDED

#include <sge/gui/image_view.hpp>
#include <sge/gui/color.hpp>
#include <sge/gui/point.hpp>
#include <sge/font/drawer.hpp>
#include <sge/renderer/image_view.hpp>
#include <sge/gui/export.hpp>
#include <sge/string.hpp>

#include <boost/optional.hpp>

namespace sge
{
namespace gui
{
namespace canvas
{
class SGE_CLASS_SYMBOL font_drawer : public font::drawer
{
	public:
	SGE_GUI_SYMBOL font_drawer(
		image_view &,
		color,
		boost::optional<string::size_type> character_pos = boost::none,
		point * = 0);

	// NOTE: this is font::drawer::size_type, _not_ font::size_type!
	SGE_GUI_SYMBOL void begin_rendering(
		size_type, 
		font::pos const &, 
		font::dim);

	SGE_GUI_SYMBOL void draw_char(
		char_type, 
		font::pos const &c, 
		font::const_image_view const &);

	SGE_GUI_SYMBOL void end_rendering();
private:
	image_view &texture_;
	color const c;
	unsigned counter;
	boost::optional<unsigned> character_pos;
	point *p;
};
}
}
}

#endif
