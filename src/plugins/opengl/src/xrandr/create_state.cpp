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
#include <sge/opengl/xrandr/create_state.hpp>
#include <sge/opengl/xrandr/get_extension.hpp>
#include <sge/opengl/xrandr/get_version.hpp>
#include <sge/opengl/xrandr/optional_extension.hpp>
#include <sge/opengl/xrandr/state.hpp>
#include <sge/opengl/xrandr/state_unique_ptr.hpp>
#include <sge/opengl/xrandr/version.hpp>
#include <awl/backends/x11/window/object.hpp>
#include <awl/backends/x11/window/event/processor_fwd.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/text.hpp>
#include <fcppt/log/_.hpp>
#include <fcppt/log/warning.hpp>


sge::opengl::xrandr::state_unique_ptr
sge::opengl::xrandr::create_state(
	awl::backends::x11::window::object &_window,
	awl::backends::x11::window::event::processor &_event_processor
)
{
	sge::opengl::xrandr::optional_extension const extension(
		sge::opengl::xrandr::get_extension(
			_window.display()
		)
	);

	if(
		!extension
	)
	{
		FCPPT_LOG_WARNING(
			sge::opengl::logger(),
			fcppt::log::_
				<< FCPPT_TEXT("xrandr extension not found")
		);

		return
			sge::opengl::xrandr::state_unique_ptr();
	}

	sge::opengl::xrandr::version const version(
		sge::opengl::xrandr::get_version(
			*extension,
			_window.display()
		)
	);

	if(
		version
		<
		sge::opengl::xrandr::version(
			1,
			3
		)
	)
	{
		FCPPT_LOG_WARNING(
			sge::opengl::logger(),
			fcppt::log::_
				<< FCPPT_TEXT("xrandr version ")
				<< version
				<< FCPPT_TEXT(" too old")
		);

		return
			sge::opengl::xrandr::state_unique_ptr();
	}

	return
		fcppt::make_unique_ptr<
			sge::opengl::xrandr::state
		>(
			*extension,
			_window,
			_event_processor
		);
}
