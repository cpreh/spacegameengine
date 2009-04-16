#ifndef SGE_GUI_FONT_INFO_HPP_INCLUDED
#define SGE_GUI_FONT_INFO_HPP_INCLUDED

#include <sge/gui/export.hpp>
#include <sge/gui/color.hpp>
#include <sge/font/metrics_fwd.hpp>

namespace sge
{
namespace gui
{
class SGE_CLASS_SYMBOL font_info
{
public:
	SGE_GUI_SYMBOL font_info(
		font::metrics_ptr,
		sge::gui::color const &);
	
	SGE_GUI_SYMBOL font::metrics_ptr const metrics() const;
	SGE_GUI_SYMBOL sge::gui::color const color() const;
private:
	font::metrics_ptr metrics_;
	sge::gui::color color_;
};
}
}

#endif
