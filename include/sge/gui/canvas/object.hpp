#ifndef SGE_GUI_CANVAS_OBJECT_HPP_INCLUDED
#define SGE_GUI_CANVAS_OBJECT_HPP_INCLUDED

#include <sge/gui/canvas/rect_type.hpp>
#include <sge/gui/canvas/line_type.hpp>
#include <sge/gui/canvas/strip_type.hpp>
#include <sge/gui/image.hpp>
#include <sge/gui/point.hpp>
#include <sge/gui/dim.hpp>
#include <sge/gui/rect.hpp>
#include <sge/gui/image_view.hpp>
#include <sge/gui/color.hpp>
#include <sge/gui/export.hpp>
#include <sge/gui/font_info.hpp>
#include <sge/font/align_h.hpp>
#include <sge/font/align_v.hpp>
#include <sge/font/flags.hpp>
#include <sge/renderer/image_view.hpp>
#include <sge/string.hpp>

#include <boost/optional.hpp>

#include <vector>

namespace sge
{
namespace gui
{
namespace canvas
{
class SGE_CLASS_SYMBOL object
{
	public:
	SGE_GUI_SYMBOL explicit object(image &);
	SGE_GUI_SYMBOL ~object();

	SGE_GUI_SYMBOL dim const size() const;
	SGE_GUI_SYMBOL rect const area() const;
	SGE_GUI_SYMBOL image_view &view();
	SGE_GUI_SYMBOL const_image_view const view() const;

	SGE_GUI_SYMBOL void draw_rect(
		rect const &,
		color,
		rect_type::type);

	SGE_GUI_SYMBOL void draw_text(
		font_info const &,
		string const &,
		point const &,
		dim const &max_size,
		font::align_h::type,
		font::align_v::type,
		font::flag_t = font::flags::default_,
		boost::optional<string::size_type> character_pos = boost::none,
		point * = 0);

	SGE_GUI_SYMBOL void draw_line(
		point const &,
		point const &,
		color,
		line_type::type type = line_type::solid);

	typedef std::vector<point> point_container;

	SGE_GUI_SYMBOL void draw_line_strip(
		point_container const &,
		color,
		line_type::type = line_type::solid,
		strip_type::type = strip_type::open);

	SGE_GUI_SYMBOL void draw_pixel(point const &,color);
	private:
	image &texture_;
	image_view view_;
};
}
}
}

#endif
