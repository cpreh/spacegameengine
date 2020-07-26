//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/cegui/system.hpp>
#include <sge/cegui/system_ref.hpp>
#include <sge/cegui/toolbox/scoped_gui_sheet.hpp>
#include <fcppt/reference_impl.hpp>
#include <fcppt/config/external_begin.hpp>
#include <CEGUI/GUIContext.h>
#include <fcppt/config/external_end.hpp>


sge::cegui::toolbox::scoped_gui_sheet::scoped_gui_sheet(
	sge::cegui::system_ref const _system,
	fcppt::reference<
		CEGUI::Window
	> const _window
)
:
	system_{
		_system
	}
{
	system_.get().gui_context().setRootWindow(
		&_window.get()
	);
}

sge::cegui::toolbox::scoped_gui_sheet::~scoped_gui_sheet()
{
	system_.get().gui_context().setRootWindow(
		nullptr
	);
}
