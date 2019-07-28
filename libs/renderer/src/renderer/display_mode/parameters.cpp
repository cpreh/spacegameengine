/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2016 Carl Philipp Reh (carlphilippreh <at> gmail.com)

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/


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
	sge::renderer::display_mode::optional_fullscreen const &_fullscreen
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
