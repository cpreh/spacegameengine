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


#include <sge/opengl/xrandr/configuration.hpp>
#include <sge/opengl/xrandr/mode.hpp>
#include <sge/opengl/xrandr/set_resolution.hpp>
#include <sge/renderer/exception.hpp>
#include <awl/backends/x11/display.hpp>
#include <awl/backends/x11/window/object.hpp>
#include <fcppt/text.hpp>
#include <fcppt/cast/size.hpp>
#include <fcppt/cast/to_signed.hpp>
#include <fcppt/optional/maybe.hpp>
#include <fcppt/config/external_begin.hpp>
#include <X11/Xlib.h>
#include <X11/extensions/Xrandr.h>
#include <fcppt/config/external_end.hpp>


void
sge::opengl::xrandr::set_resolution(
	awl::backends::x11::window::object &_window,
	sge::opengl::xrandr::configuration const &_config,
	sge::opengl::xrandr::mode const &_mode
)
{
	fcppt::optional::maybe(
		_mode.rate(),
		[
			&_window,
			&_config,
			&_mode
		]{
			if(
				::XRRSetScreenConfig(
					_window.display().get(),
					_config.get(),
					_window.get(),
					_mode.index(),
					_mode.rotation(),
					CurrentTime
				)
				!=
				Success
			)
				throw
					sge::renderer::exception{
						FCPPT_TEXT("Cannot change screen mode!")
					};
		},
		[
			&_window,
			&_config,
			&_mode
		](
			sge::renderer::display_mode::refresh_rate const _rate
		)
		{
			if(
				::XRRSetScreenConfigAndRate(
					_window.display().get(),
					_config.get(),
					_window.get(),
					_mode.index(),
					_mode.rotation(),
					fcppt::cast::size<
						short
					>(
						fcppt::cast::to_signed(
							_rate.get()
						)
					),
					CurrentTime
				)
				!= Success
			)
				throw
					sge::renderer::exception{
						FCPPT_TEXT("Cannot change screen mode with rate!")
					};
		}
	);
}
