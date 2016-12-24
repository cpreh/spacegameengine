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


#include <sge/opengl/platform/device_state.hpp>
#include <sge/opengl/platform/device_state_unique_ptr.hpp>
#include <sge/opengl/platform/system.hpp>
#include <sge/opengl/wayland/device_state.hpp>
#include <sge/opengl/wayland/system.hpp>
#include <sge/renderer/display_mode/optional_object_fwd.hpp>
#include <awl/backends/wayland/system/object_fwd.hpp>
#include <awl/window/object_fwd.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/unique_ptr_to_base.hpp>


sge::opengl::wayland::system::system(
	awl::backends::wayland::system::object &_system
)
:
	sge::opengl::platform::system()
{
}

sge::opengl::wayland::system::~system()
{
}

sge::opengl::platform::device_state_unique_ptr
sge::opengl::wayland::system::create_device_state(
	sge::renderer::display_mode::optional_object const &_display_mode,
	awl::window::object &_window
)
{
	return
		fcppt::unique_ptr_to_base<
			sge::opengl::platform::device_state
		>(
			fcppt::make_unique_ptr<
				sge::opengl::wayland::device_state
			>(
				_display_mode
			)
		);
}
