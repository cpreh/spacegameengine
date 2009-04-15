#ifndef SGE_GUI_SKINS_STANDARD_HPP_INCLUDED
#define SGE_GUI_SKINS_STANDARD_HPP_INCLUDED

#include <sge/gui/skins/base.hpp>
#include <sge/gui/color.hpp>
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
	SGE_GUI_SYMBOL standard();
	SGE_GUI_SYMBOL SGE_GUI_SKIN_DRAW_RETURN(widgets::base) fallback(
		SGE_GUI_SKIN_DRAW_PARAMS(widgets::base));
	SGE_GUI_SKIN_WIDGETS
	SGE_GUI_SYMBOL filesystem::path const cursor_path() const;
	private:
	color bgcolor,bgcolor_focused;
};
}
}
}

#endif
