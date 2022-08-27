//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_SDLINPUT_JOYPAD_FROM_EVENT_IMPL_HPP_INCLUDED
#define SGE_SDLINPUT_JOYPAD_FROM_EVENT_IMPL_HPP_INCLUDED

#include <sge/sdlinput/joypad/map.hpp>
#include <sge/sdlinput/joypad/shared_ptr.hpp>
#include <fcppt/optional/object_impl.hpp>
#include <fcppt/config/external_begin.hpp>
#include <SDL_joystick.h>
#include <fcppt/config/external_end.hpp>

namespace sge::sdlinput::joypad
{

fcppt::optional::object<sge::sdlinput::joypad::shared_ptr>
from_event_impl(sge::sdlinput::joypad::map const &, SDL_JoystickID);

}

#endif
