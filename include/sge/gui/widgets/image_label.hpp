#ifndef SGE_GUI_WIDGETS_IMAGE_HPP_INCLUDED
#define SGE_GUI_WIDGETS_IMAGE_HPP_INCLUDED

#include <sge/gui/widget.hpp>

namespace sge
{
namespace gui
{
namespace widgets
{
class image_label : public widget
{
public:
	image_label(
		widget::parent_data const &,
		widget::parameters,
		sge::gui::image const &);
};
}
}
}

#endif
