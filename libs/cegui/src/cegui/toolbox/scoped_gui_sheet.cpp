//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/cegui/system.hpp>
#include <sge/cegui/toolbox/scoped_gui_sheet.hpp>
#include <fcppt/config/external_begin.hpp>
#include <CEGUI/GUIContext.h>
#include <fcppt/config/external_end.hpp>


sge::cegui::toolbox::scoped_gui_sheet::scoped_gui_sheet(
	sge::cegui::system &_system,
	CEGUI::Window &_window
)
:
	system_(
		_system
	)
{
	system_.gui_context().setRootWindow(
		&_window
	);
}

sge::cegui::toolbox::scoped_gui_sheet::~scoped_gui_sheet()
{
	system_.gui_context().setRootWindow(
		nullptr
	);
}
