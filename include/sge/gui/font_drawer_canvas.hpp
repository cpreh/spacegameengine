#ifndef SGE_GUI_FONT_DRAWER_CANVAS_HPP_INCLUDED
#define SGE_GUI_FONT_DRAWER_CANVAS_HPP_INCLUDED

#include "types.hpp"
#include "canvas.hpp"
#include "../font/drawer.hpp"
#include "../renderer/device_fwd.hpp"
#include "../texture/part.hpp"
#include "../renderer/color.hpp"
#include "../renderer/colors.hpp"
#include "../export.hpp"

namespace sge
{
namespace gui
{
class SGE_CLASS_SYMBOL font_drawer_canvas : public font::drawer
{
public:
	SGE_SYMBOL font_drawer_canvas(canvas &);

	// NOTE: this is font::drawer::size_type, _not_ font::size_type!
	SGE_SYMBOL void begin_rendering(size_type, font::pos const &, font::dim);
	SGE_SYMBOL void draw_char(char_type, font::pos const &c, font::const_image_view const &);
	SGE_SYMBOL void end_rendering();
	void fg(color const &_fg) { fg_ = _fg; }
	void bg(color const &_bg) { bg_ = _bg; }
private:
	renderer::device_ptr rend_;
	canvas &canvas_;
	color fg_,bg_;
};
}
}

#endif
