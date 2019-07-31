//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/sdlinput/cursor/get_focus.hpp>
#include <fcppt/make_ref.hpp>
#include <fcppt/optional/make_if.hpp>
#include <fcppt/optional/reference.hpp>
#include <fcppt/config/external_begin.hpp>
#include <SDL_mouse.h>
#include <SDL_video.h>
#include <fcppt/config/external_end.hpp>


fcppt::optional::reference<
	SDL_Window
>
sge::sdlinput::cursor::get_focus()
{
	SDL_Window *const focus{
		SDL_GetMouseFocus()
	};

	return
		fcppt::optional::make_if(
			focus
			!=
			nullptr,
			[
				focus
			]{
				return
					fcppt::make_ref(
						*focus
					);
			}
		);
}
