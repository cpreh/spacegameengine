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


#include <sge/opengl/backend/context.hpp>
#include <sge/opengl/backend/current.hpp>
#include <sge/opengl/backend/current_unique_ptr.hpp>
#include <sge/opengl/sdl/context.hpp>
#include <sge/opengl/sdl/current.hpp>
#include <sge/window/object.hpp>
#include <awl/backends/sdl/window/object.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/unique_ptr_to_base.hpp>
#include <fcppt/cast/dynamic_exn.hpp>
#include <fcppt/config/external_begin.hpp>
#include <SDL_video.h>
#include <fcppt/config/external_end.hpp>


sge::opengl::sdl::context::context(
	sge::window::object &_window
)
:
	sge::opengl::backend::context{},
	window_{
		fcppt::cast::dynamic_exn<
			awl::backends::sdl::window::object &
		>(
			_window.awl_object()
		)
	},
	context_{
		SDL_GL_CreateContext(
			&this->window_.get()
		)
	}
{
}

sge::opengl::sdl::context::~context()
{
	SDL_GL_DeleteContext(
		this->context_
	);
}

sge::opengl::backend::current_unique_ptr
sge::opengl::sdl::context::activate()
{
	return
		fcppt::unique_ptr_to_base<
			sge::opengl::backend::current
		>(
			fcppt::make_unique_ptr<
				sge::opengl::sdl::current
			>(
				this->window_,
				this->context_
			)
		);
}

void
sge::opengl::sdl::context::deactivate(
	sge::opengl::backend::current_unique_ptr &&
)
{
}
