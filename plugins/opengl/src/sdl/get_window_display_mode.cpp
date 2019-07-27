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


#include <sge/opengl/sdl/get_window_display_mode.hpp>
#include <awl/backends/sdl/window/object.hpp>
#include <fcppt/optional/make_if.hpp>
#include <fcppt/optional/object_impl.hpp>
#include <fcppt/config/external_begin.hpp>
#include <SDL_video.h>
#include <fcppt/config/external_end.hpp>


fcppt::optional::object<
	SDL_DisplayMode
>
sge::opengl::sdl::get_window_display_mode(
	awl::backends::sdl::window::object &_window
)
{
	SDL_DisplayMode result{};

	return
		fcppt::optional::make_if(
			SDL_GetWindowDisplayMode(
				&_window.get(),
				&result
			)
			==
			0,
			[
				&result
			]{
				return
					result;
			}
		);
}
