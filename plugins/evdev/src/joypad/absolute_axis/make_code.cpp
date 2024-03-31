//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/evdev/device/event_type_value.hpp>
#include <sge/evdev/joypad/absolute_axis/code.hpp>
#include <sge/evdev/joypad/absolute_axis/make_code.hpp>
#include <sge/input/exception.hpp>
#include <sge/input/joypad/axis_code.hpp>
#include <fcppt/text.hpp>
#include <fcppt/cast/enum_to_int.hpp>
#include <fcppt/config/external_begin.hpp>
#include <linux/input-event-codes.h>
#include <fcppt/config/external_end.hpp>

sge::input::joypad::axis_code
sge::evdev::joypad::absolute_axis::make_code(sge::evdev::joypad::absolute_axis::code const _event)
{
  switch (fcppt::cast::enum_to_int<sge::evdev::device::event_type_value>(_event))
  {
  case ABS_X:
    return sge::input::joypad::axis_code::x;
  case ABS_Y:
    return sge::input::joypad::axis_code::y;
  case ABS_Z:
    return sge::input::joypad::axis_code::z;
  case ABS_RX:
  case ABS_RY:
  case ABS_RZ:
  case ABS_THROTTLE:
  case ABS_RUDDER:
  case ABS_WHEEL:
  case ABS_GAS:
  case ABS_BRAKE:
  case ABS_HAT0X:
  case ABS_HAT0Y:
  case ABS_HAT1X:
  case ABS_HAT1Y:
  case ABS_HAT2X:
  case ABS_HAT2Y:
  case ABS_HAT3X:
  case ABS_HAT3Y:
  case ABS_PRESSURE:
  case ABS_DISTANCE:
  case ABS_TILT_X:
  case ABS_TILT_Y:
  case ABS_TOOL_WIDTH:
  case ABS_VOLUME:
  case ABS_MISC:
  // TODO(philipp): discard multi touch stuff?
  case ABS_MT_SLOT:
  case ABS_MT_TOUCH_MAJOR:
  case ABS_MT_TOUCH_MINOR:
  case ABS_MT_WIDTH_MAJOR:
  case ABS_MT_WIDTH_MINOR:
  case ABS_MT_ORIENTATION:
  case ABS_MT_POSITION_X:
  case ABS_MT_POSITION_Y:
  case ABS_MT_TOOL_TYPE:
  case ABS_MT_BLOB_ID:
  case ABS_MT_TRACKING_ID:
  case ABS_MT_PRESSURE:
  case ABS_MT_DISTANCE:
  default:
    return sge::input::joypad::axis_code::unknown;
  }

  throw sge::input::exception{FCPPT_TEXT("Invalid absolute axis code in evdev!")};
}
