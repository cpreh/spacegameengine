//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/evdev/device/code_to_string_case.hpp>
#include <sge/evdev/device/event_type_value.hpp>
#include <sge/evdev/joypad/absolute_axis/code.hpp>
#include <sge/evdev/joypad/absolute_axis/make_string.hpp>
#include <fcppt/optional_string.hpp>
#include <fcppt/cast/enum_to_int.hpp>
#include <fcppt/config/external_begin.hpp>
#include <linux/input-event-codes.h>
#include <fcppt/config/external_end.hpp>


fcppt::optional_string
sge::evdev::joypad::absolute_axis::make_string(
	sge::evdev::joypad::absolute_axis::code const _event
)
{
	switch(
		fcppt::cast::enum_to_int<
			sge::evdev::device::event_type_value
		>(
			_event
		)
	)
	{
		SGE_EVDEV_DEVICE_CODE_TO_STRING_CASE(
			ABS_X
		);
		SGE_EVDEV_DEVICE_CODE_TO_STRING_CASE(
			ABS_Y
		);
		SGE_EVDEV_DEVICE_CODE_TO_STRING_CASE(
			ABS_Z
		);
		SGE_EVDEV_DEVICE_CODE_TO_STRING_CASE(
			ABS_RX
		);
		SGE_EVDEV_DEVICE_CODE_TO_STRING_CASE(
			ABS_RY
		);
		SGE_EVDEV_DEVICE_CODE_TO_STRING_CASE(
			ABS_RZ
		);
		SGE_EVDEV_DEVICE_CODE_TO_STRING_CASE(
			ABS_THROTTLE
		);
		SGE_EVDEV_DEVICE_CODE_TO_STRING_CASE(
			ABS_RUDDER
		);
		SGE_EVDEV_DEVICE_CODE_TO_STRING_CASE(
			ABS_WHEEL
		);
		SGE_EVDEV_DEVICE_CODE_TO_STRING_CASE(
			ABS_GAS
		);
		SGE_EVDEV_DEVICE_CODE_TO_STRING_CASE(
			ABS_BRAKE
		);
		SGE_EVDEV_DEVICE_CODE_TO_STRING_CASE(
			ABS_HAT0X
		);
		SGE_EVDEV_DEVICE_CODE_TO_STRING_CASE(
			ABS_HAT0Y
		);
		SGE_EVDEV_DEVICE_CODE_TO_STRING_CASE(
			ABS_HAT1X
		);
		SGE_EVDEV_DEVICE_CODE_TO_STRING_CASE(
			ABS_HAT1Y
		);
		SGE_EVDEV_DEVICE_CODE_TO_STRING_CASE(
			ABS_HAT2X
		);
		SGE_EVDEV_DEVICE_CODE_TO_STRING_CASE(
			ABS_HAT2Y
		);
		SGE_EVDEV_DEVICE_CODE_TO_STRING_CASE(
			ABS_HAT3X
		);
		SGE_EVDEV_DEVICE_CODE_TO_STRING_CASE(
			ABS_HAT3Y
		);
		SGE_EVDEV_DEVICE_CODE_TO_STRING_CASE(
			ABS_PRESSURE
		);
		SGE_EVDEV_DEVICE_CODE_TO_STRING_CASE(
			ABS_DISTANCE
		);
		SGE_EVDEV_DEVICE_CODE_TO_STRING_CASE(
			ABS_TILT_X
		);
		SGE_EVDEV_DEVICE_CODE_TO_STRING_CASE(
			ABS_TILT_Y
		);
		SGE_EVDEV_DEVICE_CODE_TO_STRING_CASE(
			ABS_TOOL_WIDTH
		);
		SGE_EVDEV_DEVICE_CODE_TO_STRING_CASE(
			ABS_VOLUME
		);
		SGE_EVDEV_DEVICE_CODE_TO_STRING_CASE(
			ABS_MISC
		);
		// TODO(philipp) discard multi touch stuff?
		SGE_EVDEV_DEVICE_CODE_TO_STRING_CASE(ABS_MT_SLOT);
		SGE_EVDEV_DEVICE_CODE_TO_STRING_CASE(ABS_MT_TOUCH_MAJOR);
		SGE_EVDEV_DEVICE_CODE_TO_STRING_CASE(ABS_MT_TOUCH_MINOR);
		SGE_EVDEV_DEVICE_CODE_TO_STRING_CASE(ABS_MT_WIDTH_MAJOR);
		SGE_EVDEV_DEVICE_CODE_TO_STRING_CASE(ABS_MT_WIDTH_MINOR);
		SGE_EVDEV_DEVICE_CODE_TO_STRING_CASE(ABS_MT_ORIENTATION);
		SGE_EVDEV_DEVICE_CODE_TO_STRING_CASE(ABS_MT_POSITION_X);
		SGE_EVDEV_DEVICE_CODE_TO_STRING_CASE(ABS_MT_POSITION_Y);
		SGE_EVDEV_DEVICE_CODE_TO_STRING_CASE(ABS_MT_TOOL_TYPE);
		SGE_EVDEV_DEVICE_CODE_TO_STRING_CASE(ABS_MT_BLOB_ID);
		SGE_EVDEV_DEVICE_CODE_TO_STRING_CASE(ABS_MT_TRACKING_ID);
		SGE_EVDEV_DEVICE_CODE_TO_STRING_CASE(ABS_MT_PRESSURE);
		SGE_EVDEV_DEVICE_CODE_TO_STRING_CASE(ABS_MT_DISTANCE);
	}

	return
		fcppt::optional_string{};
}
