//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/input/cursor/position.hpp>
#include <sge/input/cursor/position_unit.hpp>
#include <sge/x11input/cursor/position.hpp>
#include <fcppt/cast/float_to_int.hpp>
#include <fcppt/config/external_begin.hpp>
#include <X11/extensions/XInput2.h>
#include <fcppt/config/external_end.hpp>

sge::input::cursor::position sge::x11input::cursor::position(XIDeviceEvent const &_event)
{
  return sge::input::cursor::position(
      fcppt::cast::float_to_int<sge::input::cursor::position_unit>(_event.event_x),
      fcppt::cast::float_to_int<sge::input::cursor::position_unit>(_event.event_y));
}
