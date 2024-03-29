//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/evdev/device/code_to_string_case.hpp>
#include <sge/evdev/device/event_type_value.hpp>
#include <sge/evdev/joypad/button/code.hpp>
#include <sge/evdev/joypad/button/make_string.hpp>
#include <fcppt/optional_string.hpp>
#include <fcppt/cast/enum_to_int.hpp>
#include <fcppt/config/external_begin.hpp>
#include <linux/input-event-codes.h>
#include <fcppt/config/external_end.hpp>

fcppt::optional_string
sge::evdev::joypad::button::make_string(sge::evdev::joypad::button::code const _event)
{
  switch (fcppt::cast::enum_to_int<sge::evdev::device::event_type_value>(_event))
  {
    SGE_EVDEV_DEVICE_CODE_TO_STRING_CASE(BTN_TRIGGER);
    SGE_EVDEV_DEVICE_CODE_TO_STRING_CASE(BTN_THUMB);
    SGE_EVDEV_DEVICE_CODE_TO_STRING_CASE(BTN_THUMB2);
    SGE_EVDEV_DEVICE_CODE_TO_STRING_CASE(BTN_TOP);
    SGE_EVDEV_DEVICE_CODE_TO_STRING_CASE(BTN_TOP2);
    SGE_EVDEV_DEVICE_CODE_TO_STRING_CASE(BTN_PINKIE);
    SGE_EVDEV_DEVICE_CODE_TO_STRING_CASE(BTN_BASE);
    SGE_EVDEV_DEVICE_CODE_TO_STRING_CASE(BTN_BASE2);
    SGE_EVDEV_DEVICE_CODE_TO_STRING_CASE(BTN_BASE3);
    SGE_EVDEV_DEVICE_CODE_TO_STRING_CASE(BTN_BASE4);
    SGE_EVDEV_DEVICE_CODE_TO_STRING_CASE(BTN_BASE5);
    SGE_EVDEV_DEVICE_CODE_TO_STRING_CASE(BTN_BASE6);
    SGE_EVDEV_DEVICE_CODE_TO_STRING_CASE(BTN_DEAD);

    SGE_EVDEV_DEVICE_CODE_TO_STRING_CASE(BTN_A);
    SGE_EVDEV_DEVICE_CODE_TO_STRING_CASE(BTN_B);
    SGE_EVDEV_DEVICE_CODE_TO_STRING_CASE(BTN_C);
    SGE_EVDEV_DEVICE_CODE_TO_STRING_CASE(BTN_X);
    SGE_EVDEV_DEVICE_CODE_TO_STRING_CASE(BTN_Y);
    SGE_EVDEV_DEVICE_CODE_TO_STRING_CASE(BTN_Z);
    SGE_EVDEV_DEVICE_CODE_TO_STRING_CASE(BTN_TL);
    SGE_EVDEV_DEVICE_CODE_TO_STRING_CASE(BTN_TR);
    SGE_EVDEV_DEVICE_CODE_TO_STRING_CASE(BTN_TL2);
    SGE_EVDEV_DEVICE_CODE_TO_STRING_CASE(BTN_TR2);
    SGE_EVDEV_DEVICE_CODE_TO_STRING_CASE(BTN_SELECT);
    SGE_EVDEV_DEVICE_CODE_TO_STRING_CASE(BTN_START);
    SGE_EVDEV_DEVICE_CODE_TO_STRING_CASE(BTN_MODE);
    SGE_EVDEV_DEVICE_CODE_TO_STRING_CASE(BTN_THUMBL);
    SGE_EVDEV_DEVICE_CODE_TO_STRING_CASE(BTN_THUMBR);
    default: break;
  }

  return fcppt::optional_string();
}
