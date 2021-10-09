//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/input/joypad/shared_ptr.hpp>
#include <sge/input/joypad/event/remove.hpp>
#include <sge/sdlinput/joypad/device.hpp>
#include <sge/sdlinput/joypad/map.hpp>
#include <sge/sdlinput/joypad/remove.hpp>
#include <sge/sdlinput/joypad/shared_ptr.hpp>
#include <awl/event/base.hpp>
#include <awl/event/container.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/reference_impl.hpp>
#include <fcppt/unique_ptr_to_base.hpp>
#include <fcppt/assert/optional_error.hpp>
#include <fcppt/container/find_opt_iterator.hpp>
#include <fcppt/container/make.hpp>
#include <fcppt/config/external_begin.hpp>
#include <SDL_events.h>
#include <SDL_joystick.h>
#include <fcppt/config/external_end.hpp>

awl::event::container sge::sdlinput::joypad::remove(
    fcppt::reference<sge::sdlinput::joypad::map> const _joypads, SDL_JoyDeviceEvent const &_event)
{
  sge::sdlinput::joypad::map::iterator const iterator{FCPPT_ASSERT_OPTIONAL_ERROR(
      fcppt::container::find_opt_iterator(_joypads.get(), SDL_JoystickID{_event.which}))};

  sge::sdlinput::joypad::shared_ptr const joypad{iterator->second};

  _joypads.get().erase(iterator);

  return fcppt::container::make<awl::event::container>(fcppt::unique_ptr_to_base<awl::event::base>(
      fcppt::make_unique_ptr<sge::input::joypad::event::remove>(
          sge::input::joypad::shared_ptr{joypad})));
}
