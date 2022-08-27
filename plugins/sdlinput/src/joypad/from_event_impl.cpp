//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/sdlinput/joypad/from_event_impl.hpp>
#include <sge/sdlinput/joypad/map.hpp>
#include <sge/sdlinput/joypad/shared_ptr.hpp>
#include <fcppt/reference_impl.hpp>
#include <fcppt/container/find_opt_mapped.hpp>
#include <fcppt/optional/map.hpp>
#include <fcppt/config/external_begin.hpp>
#include <SDL_joystick.h>
#include <fcppt/config/external_end.hpp>

fcppt::optional::object<sge::sdlinput::joypad::shared_ptr> sge::sdlinput::joypad::from_event_impl(
    sge::sdlinput::joypad::map const &_joypads, SDL_JoystickID const _id)
{
  return fcppt::optional::map(
      fcppt::container::find_opt_mapped(_joypads, _id),
      [](fcppt::reference<sge::sdlinput::joypad::shared_ptr const> const _ptr)
      { return _ptr.get(); });
}
