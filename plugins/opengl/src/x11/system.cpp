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
#include <sge/opengl/x11/device_state.hpp>
#include <sge/opengl/x11/system.hpp>
#include <sge/opengl/xrandr/create_system.hpp>
#include <sge/opengl/xrandr/system.hpp>
#include <sge/renderer/display_mode/optional_object_fwd.hpp>
#include <sge/window/object_fwd.hpp>
#include <awl/backends/x11/system/object.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/unique_ptr_to_base.hpp>
#include <fcppt/log/object_fwd.hpp>
#include <fcppt/optional/deref.hpp>


sge::opengl::x11::system::system(
	fcppt::log::object &_log,
	awl::backends::x11::system::object &_awl_system
)
:
	log_{
		_log
	},
	xrandr_system_(
		sge::opengl::xrandr::create_system(
			_log,
			_awl_system.display()
		)
	)
{
}

sge::opengl::x11::system::~system()
{
}

sge::opengl::platform::device_state_unique_ptr
sge::opengl::x11::system::create_device_state(
	sge::renderer::display_mode::optional_object const &_display_mode,
	sge::window::object &_window
)
{
	return
		fcppt::unique_ptr_to_base<
			sge::opengl::platform::device_state
		>(
			fcppt::make_unique_ptr<
				sge::opengl::x11::device_state
			>(
				log_,
				fcppt::optional::deref(
					xrandr_system_
				),
				_display_mode,
				_window
			)
		);
}
