//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_OPENGL_SDL_MAKE_CURRENT_HPP_INCLUDED
#define SGE_OPENGL_SDL_MAKE_CURRENT_HPP_INCLUDED

#include <awl/backends/sdl/window/object_fwd.hpp>
#include <fcppt/config/external_begin.hpp>
#include <SDL_video.h>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace opengl
{
namespace sdl
{

void
make_current(
	awl::backends::sdl::window::object &, // NOLINT(google-runtime-references)
	SDL_GLContext
);

}
}
}

#endif
