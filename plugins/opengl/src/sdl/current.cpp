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


#include <sge/opengl/backend/current.hpp>
#include <sge/opengl/backend/fun_ptr.hpp>
#include <sge/opengl/sdl/current.hpp>
#include <sge/renderer/display_mode/vsync.hpp>
#include <awl/backends/sdl/window/object.hpp>
#include <fcppt/config/external_begin.hpp>
#include <SDL_video.h>
#include <string>
#include <fcppt/config/external_end.hpp>


sge::opengl::sdl::current::current(
	awl::backends::sdl::window::object &_window,
	SDL_GLContext const _context
)
:
	sge::opengl::backend::current{},
	window_{
		_window
	},
	context_{
		_context
	}
{
	// TODO: What does this return?
	int const result{
		SDL_GL_MakeCurrent(
			&_window.get(),
			this->context_
		)
	};
}

sge::opengl::sdl::current::~current()
{
	// TODO: Remove Current?
}

sge::opengl::backend::fun_ptr
sge::opengl::sdl::current::load_function(
	std::string const &_function
) const
{
	return
		reinterpret_cast<
			sge::opengl::backend::fun_ptr
		>(
			SDL_GL_GetProcAddress(
				_function.c_str()
			)
		);
}

void
sge::opengl::sdl::current::begin_rendering()
{
}

void
sge::opengl::sdl::current::end_rendering()
{
	SDL_GL_SwapWindow(
		&this->window_.get()
	);
}

void
sge::opengl::sdl::current::vsync(
	sge::renderer::display_mode::vsync const _vsync
)
{
}
