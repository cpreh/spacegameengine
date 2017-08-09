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
#include <sge/opengl/xrandr/mode_index.hpp>
#include <sge/opengl/xrandr/optional_refresh_rate.hpp>
#include <sge/opengl/xrandr/refresh_rate.hpp>
#include <sge/opengl/xrandr/rotation.hpp>
#include <sge/opengl/xrandr/set_resolution.hpp>
#include <sge/renderer/exception.hpp>
#include <awl/backends/x11/display.hpp>
#include <awl/backends/x11/window/base.hpp>
#include <fcppt/text.hpp>
#include <fcppt/optional/maybe.hpp>
#include <fcppt/config/external_begin.hpp>
#include <X11/X.h>
#include <X11/extensions/Xrandr.h>
#include <fcppt/config/external_end.hpp>


void
sge::opengl::xrandr::set_resolution(
	awl::backends::x11::window::base const &_window,
	sge::opengl::xrandr::configuration const &_config,
	sge::opengl::xrandr::mode_index const _mode_index,
	sge::opengl::xrandr::rotation const _rotation,
	sge::opengl::xrandr::optional_refresh_rate const &_refresh_rate
)
{
	fcppt::optional::maybe(
		_refresh_rate,
		[
			&_window,
			&_config,
			_mode_index,
			_rotation
		]{
			if(
				::XRRSetScreenConfig(
					_window.display().get(),
					_config.get(),
					_window.get(),
					_mode_index.get(),
					_rotation.get(),
					CurrentTime
				)
				!=
				0
			)
				throw
					sge::renderer::exception{
						FCPPT_TEXT("Cannot change screen mode!")
					};
		},
		[
			&_window,
			&_config,
			_mode_index,
			_rotation
		](
			sge::opengl::xrandr::refresh_rate const _rate
		)
		{
			if(
				::XRRSetScreenConfigAndRate(
					_window.display().get(),
					_config.get(),
					_window.get(),
					_mode_index.get(),
					_rotation.get(),
					_rate.get(),
					CurrentTime
				)
				!=
				0
			)
				throw
					sge::renderer::exception{
						FCPPT_TEXT("Cannot change screen mode with rate!")
					};
		}
	);
}
