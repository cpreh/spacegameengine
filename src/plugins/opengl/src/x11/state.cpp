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


#include <sge/opengl/logger.hpp>
#include <sge/opengl/device_state/object.hpp>
#include <sge/opengl/x11/state.hpp>
#include <sge/opengl/xrandr/create_state.hpp>
#include <sge/opengl/xrandr/resolution.hpp>
#include <sge/opengl/xrandr/state.hpp>
#include <sge/renderer/display_mode/optional_object.hpp>
#include <awl/backends/x11/window/object_fwd.hpp>
#include <awl/backends/x11/window/event/processor_fwd.hpp>
#include <fcppt/text.hpp>
#include <fcppt/log/_.hpp>
#include <fcppt/log/error.hpp>


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
			_event_processor
		)
	),
	resolution_()
{
	if(
		_display_mode
	)
		this->display_mode(
			_display_mode
		);
}

sge::opengl::x11::state::~state()
{
}

sge::renderer::display_mode::optional_object const
sge::opengl::x11::state::display_mode() const
{
	return
		xrandr_state_
		?
			xrandr_state_->display_mode()
		:
			sge::renderer::display_mode::optional_object()
		;
}

void
sge::opengl::x11::state::display_mode(
	sge::renderer::display_mode::optional_object const &_display_mode
)
{
	if(
		!_display_mode
	)
	{
		resolution_.reset();

		return;
	}

	if(
		!xrandr_state_
	)
	{
		FCPPT_LOG_ERROR(
			sge::opengl::logger(),
			fcppt::log::_
				<< FCPPT_TEXT("Xrandr was not found. Can't change display mode.")
		);

		return;
	}

	// TODO: Optimize this
	resolution_.reset();

	resolution_.take(
		xrandr_state_->choose_resolution(
			*_display_mode
		)
	);
}
