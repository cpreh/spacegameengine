//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/evdev/device/event_value.hpp>
#include <sge/evdev/device/fd.hpp>
#include <sge/evdev/joypad/ff/id.hpp>
#include <sge/evdev/joypad/ff/write_event.hpp>
#include <sge/input/exception.hpp>
#include <fcppt/literal.hpp>
#include <fcppt/text.hpp>
#include <fcppt/cast/to_unsigned.hpp>
#include <fcppt/config/external_begin.hpp>
#include <ctime>
#include <unistd.h>
#include <linux/input.h>
#include <linux/input-event-codes.h>
#include <sys/time.h> // NOLINT(misc-include-cleaner)
#include <fcppt/config/external_end.hpp>

void sge::evdev::joypad::ff::write_event(
    sge::evdev::device::fd &_fd,
    sge::evdev::joypad::ff::id const _id,
    sge::evdev::device::event_value const _value)
{
  input_event const event{
      // NOLINTNEXTLINE(misc-include-cleaner)
      timeval{fcppt::literal<std::time_t>(0), fcppt::literal<suseconds_t>(0)},
      EV_FF,
      fcppt::cast::to_unsigned(_id.get()),
      _value};

  if (::write(_fd.get().get(), &event, sizeof(event)) == -1)
  {
    throw sge::input::exception{FCPPT_TEXT("Writing a FF event failed")};
  }
}
