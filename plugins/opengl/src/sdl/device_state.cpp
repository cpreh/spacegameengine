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
#include <sge/opengl/sdl/device_state.hpp>
#include <sge/opengl/sdl/get_window_display_mode.hpp>
#include <sge/renderer/screen_size.hpp>
#include <sge/renderer/display_mode/container.hpp>
#include <sge/renderer/display_mode/optional_dimensions.hpp>
#include <sge/renderer/display_mode/optional_object.hpp>
#include <sge/renderer/display_mode/object.hpp>
#include <sge/renderer/display_mode/pixel_size.hpp>
#include <sge/renderer/display_mode/refresh_rate.hpp>
#include <sge/window/object.hpp>
#include <awl/backends/sdl/window/object.hpp>
#include <fcppt/cast/dynamic_exn.hpp>
#include <fcppt/cast/to_unsigned.hpp>
#include <fcppt/optional/make_if.hpp>
#include <fcppt/optional/map.hpp>
#include <fcppt/config/external_begin.hpp>
#include <SDL_video.h>
#include <fcppt/config/external_end.hpp>


sge::opengl::sdl::device_state::device_state(
	sge::renderer::display_mode::optional_object const &_display_mode,
	sge::window::object &_window
)
:
	sge::opengl::platform::device_state{},
	window_{
		fcppt::cast::dynamic_exn<
			awl::backends::sdl::window::object &
		>(
			_window.awl_object()
		)
	}
{
}

sge::opengl::sdl::device_state::~device_state()
{
}

sge::renderer::display_mode::optional_object
sge::opengl::sdl::device_state::display_mode() const
{
	return
		fcppt::optional::map(
			sge::opengl::sdl::get_window_display_mode(
				this->window_
			),
			[](
				SDL_DisplayMode const &_mode
			)
			{
				return
					sge::renderer::display_mode::object{
						sge::renderer::display_mode::pixel_size{
							sge::renderer::screen_size{
								fcppt::cast::to_unsigned(
									_mode.w
								),
								fcppt::cast::to_unsigned(
									_mode.h
								)
							}
						},
						sge::renderer::display_mode::optional_dimensions{},
						fcppt::optional::make_if(
							_mode.refresh_rate
							!=
							0,
							[
								&_mode
							]{
								return
									sge::renderer::display_mode::refresh_rate{
										fcppt::cast::to_unsigned(
											_mode.refresh_rate
										)
									};
							}
						)
					};
			}
		);
}

void
sge::opengl::sdl::device_state::display_mode(
	sge::renderer::display_mode::optional_object const &_display_mode
)
{
}

sge::renderer::display_mode::container
sge::opengl::sdl::device_state::display_modes() const
{
	// TODO:

	return
		sge::renderer::display_mode::container{};
}
