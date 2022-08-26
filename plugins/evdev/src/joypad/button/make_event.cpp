//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/evdev/device/event.hpp>
#include <sge/evdev/joypad/button/make_event.hpp>
#include <sge/input/joypad/button_id.hpp>
#include <sge/input/joypad/button_info_container_fwd.hpp>
#include <sge/input/joypad/button_pressed.hpp>
#include <sge/input/joypad/shared_ptr.hpp>
#include <sge/input/joypad/event/button.hpp>
#include <awl/event/base.hpp>
#include <awl/event/optional_base_unique_ptr.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/unique_ptr_to_base.hpp>
#include <fcppt/optional/make.hpp>

awl::event::optional_base_unique_ptr sge::evdev::joypad::button::make_event(
    sge::input::joypad::shared_ptr const &_joypad,
    sge::input::joypad::button_id const _id,
    sge::input::joypad::button_info_container const &,
    sge::evdev::device::event const _event)
{
  return fcppt::optional::make(fcppt::unique_ptr_to_base<awl::event::base>(
      fcppt::make_unique_ptr<sge::input::joypad::event::button>(
          _joypad, _id, sge::input::joypad::button_pressed{_event.get().value != 0})));
}
