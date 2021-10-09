//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/input/key/code.hpp>
#include <sge/x11input/key/code_from_event.hpp>
#include <sge/x11input/key/code_to_sym.hpp>
#include <sge/x11input/key/event_to_sge_code.hpp>
#include <sge/x11input/key/translate_sym.hpp>
#include <awl/backends/x11/display_fwd.hpp>
#include <fcppt/config/external_begin.hpp>
#include <X11/extensions/XInput2.h>
#include <fcppt/config/external_end.hpp>

sge::input::key::code sge::x11input::key::event_to_sge_code(
    awl::backends::x11::display const &_display, XIDeviceEvent const &_event)
{
  return sge::x11input::key::translate_sym(
      sge::x11input::key::code_to_sym(_display, sge::x11input::key::code_from_event(_event)));
}
