#ifndef SGE_GUI_SKINS_STANDARD_HPP_INCLUDED
#define SGE_GUI_SKINS_STANDARD_HPP_INCLUDED

#include <sge/gui/skins/base.hpp>
#include <sge/font/system_fwd.hpp>
#include <sge/gui/export.hpp>

namespace sge
{
namespace gui
{
namespace skins
{
class standard : public base
{
	public:
	SGE_GUI_SYMBOL standard(
		font::system_ptr);
	SGE_GUI_SYMBOL SGE_GUI_SKIN_DRAW_RETURN(widgets::base) fallback(
		SGE_GUI_SKIN_DRAW_PARAMS(widgets::base));
	SGE_GUI_SKIN_WIDGETS
	SGE_GUI_SYMBOL font_info const standard_font() const;
	private:
	font_info const standard_font_;
};
}
}
}

#endif
