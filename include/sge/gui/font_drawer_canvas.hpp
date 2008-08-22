#ifndef SGE_GUI_FONT_DRAWER_CANVAS_HPP_INCLUDED
#define SGE_GUI_FONT_DRAWER_CANVAS_HPP_INCLUDED

#include "types.hpp"
#include "canvas.hpp"
#include <sge/font/drawer.hpp>
#include <sge/renderer/device.hpp>
#include <sge/texture/part.hpp>
#include <sge/renderer/color.hpp>
#include <sge/renderer/colors.hpp>

namespace sge
{
namespace gui
{
class font_drawer_canvas : public font::drawer
{
public:
	font_drawer_canvas(canvas &);

	// NOTE: this is font::drawer::size_type, _not_ font::size_type!
	void begin_rendering(size_type, font::pos const &, font::dim);
	void draw_char(char_type, font::pos const &c, font::const_image_view const &);
	void end_rendering();
	void fg(renderer::color const _fg) { fg_ = _fg; }
	void bg(renderer::color const _bg) { bg_ = _bg; }
private:
	renderer::device_ptr rend_;
	canvas &canvas_;
	renderer::color fg_,bg_;
};
}
}

#endif
