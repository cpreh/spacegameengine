//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_SDLINPUT_JOYPAD_MAP_HPP_INCLUDED
#define SGE_SDLINPUT_JOYPAD_MAP_HPP_INCLUDED

#include <sge/sdlinput/joypad/shared_ptr.hpp>
#include <fcppt/config/external_begin.hpp>
#include <SDL_joystick.h>
#include <unordered_map>
#include <fcppt/config/external_end.hpp>

namespace sge::sdlinput::joypad
{

using map = std::unordered_map<SDL_JoystickID, sge::sdlinput::joypad::shared_ptr>;

}

#endif
