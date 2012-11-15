/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2012 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include <sge/opengl/device_state/object.hpp>
#include <sge/opengl/windows/change_display_settings.hpp>
#include <sge/opengl/windows/current_display_mode.hpp>
#include <sge/opengl/windows/state.hpp>
#include <sge/renderer/display_mode/object.hpp>
#include <sge/renderer/display_mode/optional_object.hpp>


sge::opengl::windows::state::state(
	sge::renderer::display_mode::optional_object const &_display_mode
)
:
	sge::opengl::device_state::object()
{
	if(
		_display_mode
	)
		sge::opengl::windows::change_display_settings(
			*_display_mode
		);
}

sge::opengl::windows::state::~state()
{
}

sge::renderer::display_mode::object const
sge::opengl::windows::state::display_mode() const
{
	// TODO!
	return
		sge::opengl::windows::current_display_mode();
}
