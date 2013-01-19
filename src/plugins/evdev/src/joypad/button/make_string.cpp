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
#include <sge/evdev/joypad/button/make_string.hpp>
#include <sge/input/info/optional_string.hpp>
#include <fcppt/assert/unreachable.hpp>
#include <fcppt/config/external_begin.hpp>
#include <linux/input.h>
#include <fcppt/config/external_end.hpp>


sge::input::info::optional_string const
sge::evdev::joypad::button::make_string(
	sge::evdev::device::event_type const _event
)
{
	switch(
		_event.get()
	)
	{
		SGE_EVDEV_DEVICE_CODE_TO_STRING_CASE(
			BTN_TRIGGER
		);
		SGE_EVDEV_DEVICE_CODE_TO_STRING_CASE(
			BTN_THUMB
		);
		SGE_EVDEV_DEVICE_CODE_TO_STRING_CASE(
			BTN_THUMB2
		);
		SGE_EVDEV_DEVICE_CODE_TO_STRING_CASE(
			BTN_TOP
		);
		SGE_EVDEV_DEVICE_CODE_TO_STRING_CASE(
			BTN_TOP2
		);
		SGE_EVDEV_DEVICE_CODE_TO_STRING_CASE(
			BTN_PINKIE
		);
		SGE_EVDEV_DEVICE_CODE_TO_STRING_CASE(
			BTN_BASE
		);
		SGE_EVDEV_DEVICE_CODE_TO_STRING_CASE(
			BTN_BASE2
		);
		SGE_EVDEV_DEVICE_CODE_TO_STRING_CASE(
			BTN_BASE3
		);
		SGE_EVDEV_DEVICE_CODE_TO_STRING_CASE(
			BTN_BASE4
		);
		SGE_EVDEV_DEVICE_CODE_TO_STRING_CASE(
			BTN_BASE5
		);
		SGE_EVDEV_DEVICE_CODE_TO_STRING_CASE(
			BTN_BASE6
		);
		SGE_EVDEV_DEVICE_CODE_TO_STRING_CASE(
			BTN_DEAD
		);

		SGE_EVDEV_DEVICE_CODE_TO_STRING_CASE(
			BTN_A
		);
		SGE_EVDEV_DEVICE_CODE_TO_STRING_CASE(
			BTN_B
		);
		SGE_EVDEV_DEVICE_CODE_TO_STRING_CASE(
			BTN_C
		);
		SGE_EVDEV_DEVICE_CODE_TO_STRING_CASE(
			BTN_X
		);
		SGE_EVDEV_DEVICE_CODE_TO_STRING_CASE(
			BTN_Y
		);
		SGE_EVDEV_DEVICE_CODE_TO_STRING_CASE(
			BTN_Z
		);
		SGE_EVDEV_DEVICE_CODE_TO_STRING_CASE(
			BTN_TL
		);
		SGE_EVDEV_DEVICE_CODE_TO_STRING_CASE(
			BTN_TR
		);
		SGE_EVDEV_DEVICE_CODE_TO_STRING_CASE(
			BTN_TL2
		);
		SGE_EVDEV_DEVICE_CODE_TO_STRING_CASE(
			BTN_TR2
		);
		SGE_EVDEV_DEVICE_CODE_TO_STRING_CASE(
			BTN_SELECT
		);
		SGE_EVDEV_DEVICE_CODE_TO_STRING_CASE(
			BTN_START
		);
		SGE_EVDEV_DEVICE_CODE_TO_STRING_CASE(
			BTN_MODE
		);
		SGE_EVDEV_DEVICE_CODE_TO_STRING_CASE(
			BTN_THUMBL
		);
		SGE_EVDEV_DEVICE_CODE_TO_STRING_CASE(
			BTN_THUMBR
		);
		default:
			return
				sge::input::info::optional_string();
	}
}
