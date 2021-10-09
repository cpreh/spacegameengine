//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/sdlinput/joypad/from_event_impl.hpp>
#include <sge/sdlinput/joypad/map.hpp>
#include <sge/sdlinput/joypad/shared_ptr.hpp>
#include <fcppt/assert/optional_error.hpp>
#include <fcppt/container/find_opt_mapped.hpp>
#include <fcppt/config/external_begin.hpp>
#include <SDL_joystick.h>
#include <fcppt/config/external_end.hpp>

sge::sdlinput::joypad::shared_ptr sge::sdlinput::joypad::from_event_impl(
    sge::sdlinput::joypad::map const &_joypads, SDL_JoystickID const _id)
{
  return FCPPT_ASSERT_OPTIONAL_ERROR(fcppt::container::find_opt_mapped(_joypads, _id)).get();
}
