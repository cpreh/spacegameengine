//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/input/keyboard/key_id.hpp>
#include <sge/x11input/key/code_from_event.hpp>
#include <sge/x11input/keyboard/key_id.hpp>
#include <fcppt/cast/to_unsigned.hpp>
#include <fcppt/config/external_begin.hpp>
#include <X11/extensions/XInput2.h>
#include <fcppt/config/external_end.hpp>

sge::input::keyboard::key_id sge::x11input::keyboard::key_id(XIDeviceEvent const &_event)
{
  return sge::input::keyboard::key_id{
      fcppt::cast::to_unsigned(sge::x11input::key::code_from_event(_event).get())};
}
