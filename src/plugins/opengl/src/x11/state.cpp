/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2013 Carl Philipp Reh (sefi@s-e-f-i.de)

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
#include <sge/opengl/x11/state.hpp>
#include <sge/opengl/xrandr/create_state.hpp>
#include <sge/opengl/xrandr/state.hpp>
#include <sge/renderer/display_mode/object.hpp>
#include <sge/renderer/display_mode/optional_object_fwd.hpp>
#include <awl/backends/x11/window/object_fwd.hpp>
#include <awl/backends/x11/window/event/processor_fwd.hpp>
#include <fcppt/assert/error.hpp>


sge::opengl::x11::state::state(
	sge::renderer::display_mode::optional_object const &_display_mode,
	awl::backends::x11::window::object &_window,
	awl::backends::x11::window::event::processor &_event_processor
)
:
	sge::opengl::device_state::object(),
	xrandr_state_(
		sge::opengl::xrandr::create_state(
			_window,
			_event_processor,
			_display_mode
		)
	)
{
	// TODO: Make this optional!
	FCPPT_ASSERT_ERROR(
		xrandr_state_
	);
}

sge::opengl::x11::state::~state()
{
}

sge::renderer::display_mode::object const
sge::opengl::x11::state::display_mode() const
{
	return
		xrandr_state_->display_mode();
}
