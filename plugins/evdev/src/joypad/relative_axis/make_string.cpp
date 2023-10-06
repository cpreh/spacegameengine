//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/evdev/device/code_to_string_case.hpp>
#include <sge/evdev/device/event_type_value.hpp>
#include <sge/evdev/joypad/relative_axis/code.hpp>
#include <sge/evdev/joypad/relative_axis/make_string.hpp>
#include <fcppt/optional_string.hpp>
#include <fcppt/cast/enum_to_int.hpp>
#include <fcppt/config/external_begin.hpp>
#include <linux/input-event-codes.h>
#include <fcppt/config/external_end.hpp>

fcppt::optional_string
sge::evdev::joypad::relative_axis::make_string(sge::evdev::joypad::relative_axis::code const _event)
{
  switch (fcppt::cast::enum_to_int<sge::evdev::device::event_type_value>(_event))
  {
    SGE_EVDEV_DEVICE_CODE_TO_STRING_CASE(REL_X);
    SGE_EVDEV_DEVICE_CODE_TO_STRING_CASE(REL_Y);
    SGE_EVDEV_DEVICE_CODE_TO_STRING_CASE(REL_Z);
    SGE_EVDEV_DEVICE_CODE_TO_STRING_CASE(REL_RX);
    SGE_EVDEV_DEVICE_CODE_TO_STRING_CASE(REL_RY);
    SGE_EVDEV_DEVICE_CODE_TO_STRING_CASE(REL_RZ);
    SGE_EVDEV_DEVICE_CODE_TO_STRING_CASE(REL_HWHEEL);
    SGE_EVDEV_DEVICE_CODE_TO_STRING_CASE(REL_DIAL);
    SGE_EVDEV_DEVICE_CODE_TO_STRING_CASE(REL_WHEEL);
    SGE_EVDEV_DEVICE_CODE_TO_STRING_CASE(REL_MISC);
    default: break;
  }

  return fcppt::optional_string{};
}
