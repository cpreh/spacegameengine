//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/cegui/system.hpp>
#include <sge/cegui/to_cegui_string.hpp>
#include <sge/cegui/toolbox/scoped_layout.hpp>
#include <fcppt/filesystem/path_to_string.hpp>
#include <fcppt/config/external_begin.hpp>
#include <CEGUI/WindowManager.h>
#include <filesystem>
#include <fcppt/config/external_end.hpp>


sge::cegui::toolbox::scoped_layout::scoped_layout(
	sge::cegui::system &_system,
	std::filesystem::path const &_path
)
:
	system_(
		_system
	),
	window_(
		system_.window_manager().loadLayoutFromFile(
			sge::cegui::to_cegui_string(
				fcppt::filesystem::path_to_string(
					_path
				)
			),
			"",
			nullptr,
			nullptr
		)
	)
{
}

sge::cegui::toolbox::scoped_layout::~scoped_layout()
{
	system_.window_manager().destroyWindow(
		window_
	);
}

CEGUI::Window &
sge::cegui::toolbox::scoped_layout::window() const
{
	return
		*window_;
}
