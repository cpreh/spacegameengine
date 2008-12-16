#ifndef SGE_GUI_CANVAS_DRAWER_HPP_INCLUDED
#define SGE_GUI_CANVAS_DRAWER_HPP_INCLUDED

#include "../types.hpp"
#include "../../font/drawer.hpp"
#include "../../renderer/image_view.hpp"
#include "../../export.hpp"

namespace sge
{
namespace gui
{
namespace canvas
{
class SGE_CLASS_SYMBOL font_drawer : public font::drawer
{
	public:
	SGE_SYMBOL font_drawer(image_view &,color);

	// NOTE: this is font::drawer::size_type, _not_ font::size_type!
	SGE_SYMBOL void begin_rendering(
		size_type, 
		font::pos const &, 
		font::dim);

	SGE_SYMBOL void draw_char(
		char_type, 
		font::pos const &c, 
		font::const_image_view const &);

	SGE_SYMBOL void end_rendering();
private:
	image_view &texture_;
	color const c;
};
}
}
}

#endif
