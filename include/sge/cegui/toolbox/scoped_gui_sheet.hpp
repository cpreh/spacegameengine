#ifndef SGE_CEGUI_TOOLBOX_SCOPED_GUI_SHEET_HPP_INCLUDED
#define SGE_CEGUI_TOOLBOX_SCOPED_GUI_SHEET_HPP_INCLUDED

#include <sge/cegui/symbol.hpp>
#include <fcppt/noncopyable.hpp>

namespace CEGUI
{
class Window;
}

namespace sge
{
namespace cegui
{
namespace toolbox
{

class scoped_gui_sheet
{
	FCPPT_NONCOPYABLE(
		scoped_gui_sheet
	);
public:
	SGE_CEGUI_SYMBOL
	explicit scoped_gui_sheet(
		CEGUI::Window &
	);

	SGE_CEGUI_SYMBOL
	~scoped_gui_sheet();
};

}
}
}

#endif
