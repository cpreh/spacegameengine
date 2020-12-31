//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/renderer/display_mode/fullscreen.hpp>
#include <sge/renderer/display_mode/object.hpp>
#include <sge/renderer/display_mode/optional_fullscreen.hpp>
#include <sge/renderer/display_mode/optional_object.hpp>
#include <sge/renderer/display_mode/parameters.hpp>
#include <sge/renderer/display_mode/vsync.hpp>
#include <fcppt/optional/map.hpp>


sge::renderer::display_mode::parameters::parameters(
	sge::renderer::display_mode::vsync const _vsync,
	sge::renderer::display_mode::optional_object const &_display_mode
)
:
	sge::renderer::display_mode::parameters::parameters(
		_vsync,
		fcppt::optional::map(
			_display_mode,
			[](
				sge::renderer::display_mode::object const &_mode
			)
			{
				return
					sge::renderer::display_mode::fullscreen{
						_mode
					};
			}
		)
	)
{
}

sge::renderer::display_mode::parameters::parameters(
	sge::renderer::display_mode::vsync const _vsync,
	sge::renderer::display_mode::optional_fullscreen const _fullscreen
)
:
	vsync_(
		_vsync
	),
	fullscreen_(
		_fullscreen
	)
{
}

sge::renderer::display_mode::vsync
sge::renderer::display_mode::parameters::vsync() const
{
	return
		vsync_;
}

sge::renderer::display_mode::optional_fullscreen const &
sge::renderer::display_mode::parameters::fullscreen() const
{
	return
		fullscreen_;
}
