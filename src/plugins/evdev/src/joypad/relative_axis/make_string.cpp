/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2012 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include <sge/evdev/device/event_type.hpp>
#include <sge/evdev/joypad/relative_axis/make_string.hpp>
#include <sge/input/info/optional_string.hpp>
#include <fcppt/assert/unreachable.hpp>
#include <fcppt/config/external_begin.hpp>
#include <linux/input.h>
#include <fcppt/config/external_end.hpp>


sge::input::info::optional_string const
sge::evdev::joypad::relative_axis::make_string(
	sge::evdev::device::event_type const _event
)
{
#define SGE_EVDEV_JOYPAD_RELATIVE_AXIS_MAKE_STRING_CASE(\
	value\
)\
case value:\
	return \
		sge::input::info::optional_string(\
			FCPPT_PP_STRINGIZE(\
				value\
			)\
		)

	switch(
		_event.get()
	)
	{
		SGE_EVDEV_JOYPAD_RELATIVE_AXIS_MAKE_STRING_CASE(
			REL_X
		);
		SGE_EVDEV_JOYPAD_RELATIVE_AXIS_MAKE_STRING_CASE(
			REL_Y
		);
		SGE_EVDEV_JOYPAD_RELATIVE_AXIS_MAKE_STRING_CASE(
			REL_Z
		);
		SGE_EVDEV_JOYPAD_RELATIVE_AXIS_MAKE_STRING_CASE(
			REL_RX
		);
		SGE_EVDEV_JOYPAD_RELATIVE_AXIS_MAKE_STRING_CASE(
			REL_RY
		);
		SGE_EVDEV_JOYPAD_RELATIVE_AXIS_MAKE_STRING_CASE(
			REL_RZ
		);
		SGE_EVDEV_JOYPAD_RELATIVE_AXIS_MAKE_STRING_CASE(
			REL_HWHEEL
		);
		SGE_EVDEV_JOYPAD_RELATIVE_AXIS_MAKE_STRING_CASE(
			REL_DIAL
		);
		SGE_EVDEV_JOYPAD_RELATIVE_AXIS_MAKE_STRING_CASE(
			REL_WHEEL
		);
		SGE_EVDEV_JOYPAD_RELATIVE_AXIS_MAKE_STRING_CASE(
			REL_MISC
		);
	}

	FCPPT_ASSERT_UNREACHABLE;
}
