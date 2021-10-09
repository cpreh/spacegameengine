//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/x11input/key/code.hpp>
#include <sge/x11input/key/code_from_event.hpp>
#include <fcppt/config/external_begin.hpp>
#include <X11/extensions/XInput2.h>
#include <fcppt/config/external_end.hpp>

sge::x11input::key::code sge::x11input::key::code_from_event(XIDeviceEvent const &_event)
{
  return sge::x11input::key::code(_event.detail);
}
