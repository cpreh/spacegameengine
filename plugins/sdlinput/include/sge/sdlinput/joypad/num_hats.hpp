//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_SDLINPUT_JOYPAD_NUM_HATS_HPP_INCLUDED
#define SGE_SDLINPUT_JOYPAD_NUM_HATS_HPP_INCLUDED

#include <sge/input/info/id.hpp>
#include <fcppt/config/external_begin.hpp>
#include <SDL_joystick.h>
#include <fcppt/config/external_end.hpp>

namespace sge::sdlinput::joypad
{

sge::input::info::id num_hats(SDL_Joystick & // NOLINT(google-runtime-references)
); // NOLINT(google-runtime-references)

}

#endif
