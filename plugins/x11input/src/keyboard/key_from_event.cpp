//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/input/keyboard/key.hpp>
#include <sge/x11input/key/event_to_sge_code.hpp>
#include <sge/x11input/keyboard/key_from_event.hpp>
#include <sge/x11input/keyboard/key_id.hpp>
#include <awl/backends/x11/display_fwd.hpp>
#include <fcppt/config/external_begin.hpp>
#include <X11/extensions/XInput2.h>
#include <fcppt/config/external_end.hpp>

sge::input::keyboard::key sge::x11input::keyboard::key_from_event(
    awl::backends::x11::display const &_display, XIDeviceEvent const &_event)
{
  return sge::input::keyboard::key{
      sge::x11input::key::event_to_sge_code(_display, _event),
      sge::x11input::keyboard::key_id(_event)};
}
