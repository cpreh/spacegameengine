//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/x11input/event/base.hpp>
#include <awl/backends/x11/system/event/generic.hpp>
#include <fcppt/config/external_begin.hpp>
#include <X11/extensions/XInput2.h>
#include <cstring>
#include <fcppt/config/external_end.hpp>

XIEvent sge::x11input::event::base(awl::backends::x11::system::event::generic const &_event)
{
  // Copy the head of the event to avoid strict-aliasing problems
  XIEvent result;

  std::memcpy(&result, _event.data(), sizeof(XIEvent));

  return result;
}
