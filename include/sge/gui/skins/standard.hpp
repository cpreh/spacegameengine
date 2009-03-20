#ifndef SGE_GUI_SKINS_STANDARD_HPP_INCLUDED
#define SGE_GUI_SKINS_STANDARD_HPP_INCLUDED

#include <sge/gui/skin.hpp>
#include <sge/gui/color.hpp>
#include <sge/export.hpp>

namespace sge
{
namespace gui
{
namespace skins
{
class standard : public skin
{
	public:
	SGE_SYMBOL standard();
	SGE_SYMBOL SGE_GUI_SKIN_DRAW_RETURN(widget) fallback(
		SGE_GUI_SKIN_DRAW_PARAMS(widget));
	SGE_GUI_SKIN_WIDGETS
	SGE_SYMBOL filesystem::path const cursor_path() const;
	private:
	color bgcolor,bgcolor_focused;
};
}
}
}

#endif
