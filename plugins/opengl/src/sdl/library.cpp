//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/opengl/sdl/library.hpp>
#include <sge/renderer/exception.hpp>
#include <fcppt/text.hpp>
#include <fcppt/config/external_begin.hpp>
#include <SDL_video.h>
#include <fcppt/config/external_end.hpp>


sge::opengl::sdl::library::library()
{
	if(
		SDL_GL_LoadLibrary(
			nullptr
		)
		!=
		0
	)
		throw
			sge::renderer::exception{
				FCPPT_TEXT("Failed to load SDL OpenGL library!")
			};
}

sge::opengl::sdl::library::~library()
{
	SDL_GL_UnloadLibrary();
}
