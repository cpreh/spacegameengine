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
#include <sge/opengl/windows/change_display_settings.hpp>
#include <sge/opengl/windows/current_display_mode.hpp>
#include <sge/opengl/windows/device_state.hpp>
#include <sge/renderer/display_mode/optional_fullscreen.hpp>
#include <sge/renderer/display_mode/optional_object.hpp>
#include <fcppt/log/object_fwd.hpp>
#include <fcppt/optional/maybe_void.hpp>


sge::opengl::windows::device_state::device_state(
	fcppt::log::object &_log,
	sge::renderer::display_mode::optional_fullscreen const &_opt_fullscreen
)
:
	sge::opengl::platform::device_state(),
	log_{
		_log
	}
{
	fcppt::optional::maybe_void(
		_opt_fullscreen,
		[
			this
		](
			sge::renderer::display_mode::fullscreen const &_fullscreen
		)
		{
			this->fullscreen(
				_fullscreen
			);
		}
	);
}

sge::opengl::windows::device_state::~device_state()
{
}

sge::renderer::display_mode::optional_object
sge::opengl::windows::device_state::display_mode() const
{
	// TODO
	return
		sge::renderer::display_mode::optional_object(
			sge::opengl::windows::current_display_mode()
		);
}

void
sge::opengl::windows::device_state::fullscreen(
	sge::renderer::display_mode::optional_fullscren const &_fullscreen
)
{
	// TODO!
/*
	sge::opengl::windows::change_display_settings(
		this->log_,
		_fullscreen
	);*/
}
