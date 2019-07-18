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


#include <sge/opengl/sdl/visual.hpp>
#include <sge/renderer/pixel_format/object.hpp>
#include <awl/backends/sdl/visual/flags.hpp>
#include <awl/backends/sdl/visual/object.hpp>
#include <fcppt/config/external_begin.hpp>
#include <SDL_video.h>
#include <fcppt/config/external_end.hpp>


sge::opengl::sdl::visual::visual(
	sge::renderer::pixel_format::object const &_pixel_format
)
:
	awl::backends::sdl::visual::object{
		awl::backends::sdl::visual::flags{
			SDL_WINDOW_OPENGL
		}
	},
	pixel_format_{
		_pixel_format
	}
{
}

sge::opengl::sdl::visual::~visual()
{
}

void
sge::opengl::sdl::visual::apply() const
{
	// TODO: Apply pixel_format
}
