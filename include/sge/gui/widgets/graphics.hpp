#ifndef SGE_GUI_WIDGETS_GRAPHICS_HPP_INCLUDED
#define SGE_GUI_WIDGETS_GRAPHICS_HPP_INCLUDED

#include <sge/gui/widgets/base.hpp>
#include <sge/gui/export.hpp>

namespace sge
{
namespace gui
{
namespace widgets
{
class graphics : public base
{

public:
	SGE_GUI_SYMBOL graphics(
		widgets::parent_data const &,
		widgets::parameters,
		const_image_ptr);
};
}

}
}

#endif
