#include <sge/cegui/toolbox/scoped_gui_sheet.hpp>
#include <CEGUI/CEGUISystem.h>

sge::cegui::toolbox::scoped_gui_sheet::scoped_gui_sheet(
	CEGUI::Window &_window
)
{
	CEGUI::System::getSingleton().setGUISheet(
		&_window
	);
}

sge::cegui::toolbox::scoped_gui_sheet::~scoped_gui_sheet()
{
	CEGUI::System::getSingleton().setGUISheet(
		0
	);
}
