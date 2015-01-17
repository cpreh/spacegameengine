/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2015 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#include <sge/opengl/platform/device_state.hpp>
#include <sge/opengl/windows/change_display_settings.hpp>
#include <sge/opengl/windows/current_display_mode.hpp>
#include <sge/opengl/windows/device_state.hpp>
#include <sge/renderer/display_mode/optional_object.hpp>


sge::opengl::windows::device_state::device_state(
	sge::renderer::display_mode::optional_object const &_display_mode
)
:
	sge::opengl::platform::device_state()
{
	if(
		_display_mode
	)
		sge::opengl::windows::change_display_settings(
			*_display_mode
		);
}

sge::opengl::windows::device_state::~device_state()
{
}

sge::renderer::display_mode::optional_object const
sge::opengl::windows::device_state::display_mode() const
{
	return
		sge::renderer::display_mode::optional_object(
			sge::opengl::windows::current_display_mode()
		);
}

void
sge::opengl::windows::device_state::display_mode(
	sge::renderer::display_mode::optional_object const &_display_mode
)
{
	// TODO!
}
