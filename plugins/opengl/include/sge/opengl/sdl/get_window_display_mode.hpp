//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_OPENGL_SDL_GET_WINDOW_DISPLAY_MODE_HPP_INCLUDED
#define SGE_OPENGL_SDL_GET_WINDOW_DISPLAY_MODE_HPP_INCLUDED

#include <awl/backends/sdl/window/object_fwd.hpp>
#include <fcppt/optional/object_impl.hpp>
#include <fcppt/config/external_begin.hpp>
#include <SDL_video.h>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace opengl
{
namespace sdl
{

fcppt::optional::object<
	SDL_DisplayMode
>
get_window_display_mode(
	awl::backends::sdl::window::object &
);

}
}
}

#endif
