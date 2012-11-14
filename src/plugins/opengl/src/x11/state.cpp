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


#include <sge/opengl/device_state/context.hpp>
#include <sge/opengl/device_state/create_context.hpp>
#include <sge/opengl/device_state/object.hpp>
#include <sge/opengl/x11/state.hpp>
#include <sge/renderer/display_mode/object.hpp>
#include <sge/renderer/parameters/object.hpp>
#include <awl/backends/x11/window/object.hpp>


sge::opengl::x11::state::state(
	sge::opengl::context::system::object &_system_context,
	sge::renderer::parameters::object const &_parameters,
	awl::backends::x11::window::object &_window
)
:
	sge::opengl::device_state::object(),
	context_(
		sge::opengl::device_state::create_context(
			_system_context,
			_window
		)
	),
	scoped_current_(
		*context_
	),
	xrandr_state_(
		_window,
		_parameters.display_mode()
	)
{
	context_->vsync(
		_parameters.vsync()
	);
}

sge::opengl::x11::state::~state()
{
}

sge::opengl::device_state::context &
sge::opengl::x11::state::context()
{
	return *context_;
}

sge::renderer::display_mode::object const
sge::opengl::x11::state::display_mode() const
{
	return
		xrandr_state_.display_mode();
}
