//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_SDLINPUT_CURSOR_GET_FOCUS_HPP_INCLUDED
#define SGE_SDLINPUT_CURSOR_GET_FOCUS_HPP_INCLUDED

#include <fcppt/optional/reference.hpp>
#include <fcppt/config/external_begin.hpp>
#include <SDL_video.h>
#include <fcppt/config/external_end.hpp>

namespace sge::sdlinput::cursor
{

fcppt::optional::reference<SDL_Window> get_focus();

}

#endif
