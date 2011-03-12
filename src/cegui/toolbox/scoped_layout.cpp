#include <sge/cegui/toolbox/scoped_layout.hpp>
#include <sge/cegui/to_cegui_string.hpp>
#include <CEGUI/CEGUIWindowManager.h>
#include <CEGUI/CEGUISystem.h>
#include <fcppt/filesystem/path_to_string.hpp>

sge::cegui::toolbox::scoped_layout::scoped_layout(
	fcppt::filesystem::path const &_path,
	sge::charconv::system_ptr const _charconv_system)
:
	window_(
		CEGUI::WindowManager::getSingleton().loadWindowLayout( 
			sge::cegui::to_cegui_string(
				fcppt::filesystem::path_to_string(
					_path),
				_charconv_system)))
{
	CEGUI::System::getSingleton().setGUISheet(
		window_);
}

sge::cegui::toolbox::scoped_layout::~scoped_layout()
{
	CEGUI::WindowManager::getSingleton().destroyWindow(
		window_);
}
