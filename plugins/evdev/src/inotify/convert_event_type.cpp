//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/evdev/inotify/convert_event_type.hpp>
#include <sge/evdev/inotify/event_type.hpp>
#include <sge/input/exception.hpp>
#include <fcppt/text.hpp>
#include <fcppt/config/external_begin.hpp>
#include <sys/inotify.h>
#include <cstdint>
#include <fcppt/config/external_end.hpp>

sge::evdev::inotify::event_type sge::evdev::inotify::convert_event_type(std::uint32_t const _mask)
{
  if ((_mask & IN_CREATE) != 0 // NOLINT(hicpp-signed-bitwise)
  )
  {
    return sge::evdev::inotify::event_type::add;
  }

  if ((_mask & IN_DELETE) != 0 // NOLINT(hicpp-signed-bitwise)
  )
  {
    return sge::evdev::inotify::event_type::remove;
  }

  if ((_mask & IN_ATTRIB) != 0 // NOLINT(hicpp-signed-bitwise)
  )
  {
    return sge::evdev::inotify::event_type::attrib;
  }

  throw sge::input::exception{FCPPT_TEXT("Invalid inotify mask!")};
}
