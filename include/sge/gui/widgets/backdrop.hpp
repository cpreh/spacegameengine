#ifndef SGE_GUI_WIDGETS_BACKDROP_HPP_INCLUDED
#define SGE_GUI_WIDGETS_BACKDROP_HPP_INCLUDED

#include <sge/gui/widget.hpp>
#include <sge/export.hpp>

namespace sge
{
namespace gui
{
namespace widgets
{
class SGE_CLASS_SYMBOL backdrop : public widget
{
	public:
	SGE_SYMBOL backdrop(
		parent_data const &,
		parameters);
};
}
}
}

#endif
