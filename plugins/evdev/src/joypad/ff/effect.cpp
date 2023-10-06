//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/evdev/device/event_value.hpp>
#include <sge/evdev/device/fd_ref.hpp>
#include <sge/evdev/joypad/button/event_map.hpp>
#include <sge/evdev/joypad/ff/convert_effect.hpp>
#include <sge/evdev/joypad/ff/effect.hpp>
#include <sge/evdev/joypad/ff/write_event.hpp>
#include <sge/input/joypad/ff/effect.hpp>
#include <sge/input/joypad/ff/optional_play_count.hpp>
#include <sge/input/joypad/ff/parameters_fwd.hpp>
#include <sge/input/joypad/ff/play_count.hpp>
#include <fcppt/literal.hpp>
#include <fcppt/cast/size.hpp>
#include <fcppt/cast/to_signed.hpp>
#include <fcppt/optional/maybe.hpp>
#include <fcppt/config/external_begin.hpp>
#include <limits>
#include <fcppt/config/external_end.hpp>

sge::evdev::joypad::ff::effect::effect(
    sge::evdev::device::fd_ref const _fd,
    sge::evdev::joypad::button::event_map const &_buttons,
    sge::input::joypad::ff::parameters const &_parameters)
    : sge::input::joypad::ff::effect(),
      fd_{_fd},
      uploaded_effect_{_fd, sge::evdev::joypad::ff::convert_effect(_buttons, _parameters)}
{
}

sge::evdev::joypad::ff::effect::~effect() = default;

void sge::evdev::joypad::ff::effect::play(
    sge::input::joypad::ff::optional_play_count const _opt_play_count)
{
  sge::evdev::joypad::ff::write_event(
      fd_.get(),
      uploaded_effect_.id(),
      fcppt::optional::maybe(
          _opt_play_count,
          []
          {
            // TODO(philipp): What do we put here?
            return std::numeric_limits<sge::evdev::device::event_value>::max();
          },
          [](sge::input::joypad::ff::play_count const _play_count)
          {
            return fcppt::cast::size<sge::evdev::device::event_value>(
                fcppt::cast::to_signed(_play_count.get()));
          }));
}

void sge::evdev::joypad::ff::effect::stop()
{
  sge::evdev::joypad::ff::write_event(
      fd_.get(), uploaded_effect_.id(), fcppt::literal<sge::evdev::device::event_value>(0));
}
