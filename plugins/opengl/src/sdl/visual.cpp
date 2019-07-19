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
#include <sge/renderer/exception.hpp>
#include <sge/renderer/pixel_format/object.hpp>
#include <awl/backends/sdl/visual/flags.hpp>
#include <awl/backends/sdl/visual/object.hpp>
#include <fcppt/output_to_fcppt_string.hpp>
#include <fcppt/text.hpp>
#include <fcppt/cast/enum_to_underlying.hpp>
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
	auto const set_attribute(
		[](
			SDL_GLattr const _attr,
			int const _value
		)
		{
			if(
				SDL_GL_SetAttribute(
					_attr,
					_value
				)
				!=
				0
			)
				throw
					sge::renderer::exception{
						FCPPT_TEXT("Failed to set SDL GL attribute ")
						+
						fcppt::output_to_fcppt_string(
							fcppt::cast::enum_to_underlying(
								_attr
							)
						)
						+
						FCPPT_TEXT(" to ")
						+
						fcppt::output_to_fcppt_string(
							_value
						)
						+
						FCPPT_TEXT("!")
					};
		}
	);

	set_attribute(
		SDL_GL_DOUBLEBUFFER,
		1
	);

	// TODO: Apply pixel_format

}
