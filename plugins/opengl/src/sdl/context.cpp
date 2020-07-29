//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/opengl/backend/context.hpp>
#include <sge/opengl/backend/current.hpp>
#include <sge/opengl/backend/current_unique_ptr.hpp>
#include <sge/opengl/sdl/context.hpp>
#include <sge/opengl/sdl/current.hpp>
#include <sge/window/object.hpp>
#include <sge/window/object_ref.hpp>
#include <awl/backends/sdl/window/object.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/unique_ptr_to_base.hpp>
#include <fcppt/cast/dynamic_exn.hpp>
#include <fcppt/config/external_begin.hpp>
#include <SDL_video.h>
#include <fcppt/config/external_end.hpp>


sge::opengl::sdl::context::context(
	sge::window::object_ref const _window
)
:
	sge::opengl::backend::context{},
	window_{
		fcppt::cast::dynamic_exn<
			awl::backends::sdl::window::object &
		>(
			_window.get().awl_object()
		)
	},
	context_{
		SDL_GL_CreateContext(
			&this->window_.get().get().get()
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
