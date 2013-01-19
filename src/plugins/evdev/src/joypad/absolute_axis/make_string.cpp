/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2013 Carl Philipp Reh (sefi@s-e-f-i.de)

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/


#include <sge/evdev/device/code_to_string_case.hpp>
#include <sge/evdev/device/event_type.hpp>
#include <sge/evdev/joypad/absolute_axis/make_string.hpp>
#include <sge/input/info/optional_string.hpp>
#include <fcppt/assert/unreachable.hpp>
#include <fcppt/config/external_begin.hpp>
#include <linux/input.h>
#include <fcppt/config/external_end.hpp>


sge::input::info::optional_string const
sge::evdev::joypad::absolute_axis::make_string(
	sge::evdev::device::event_type const _event
)
{
	switch(
		_event.get()
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
		// TODO); discard multi touch stuff?
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

	FCPPT_ASSERT_UNREACHABLE;
}
