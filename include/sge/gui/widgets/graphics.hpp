#ifndef SGE_GUI_WIDGETS_GRAPHICS_HPP_INCLUDED
#define SGE_GUI_WIDGETS_GRAPHICS_HPP_INCLUDED

#include <sge/gui/widget.hpp>
#include <sge/export.hpp>

namespace sge
{
namespace gui
{
namespace widgets
{
class graphics : public widget
{

public:
	SGE_SYMBOL graphics(
		widget::parent_data const &,
		widget::parameters,
		const_image_ptr);
};
}

}
}

#endif
