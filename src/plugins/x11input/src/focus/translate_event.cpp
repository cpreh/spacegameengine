/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2015 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#include <sge/x11input/focus/translate_event.hpp>
#include <fcppt/assert/unreachable.hpp>
#include <fcppt/cast/float_to_int.hpp>
#include <fcppt/cast/to_unsigned.hpp>
#include <fcppt/config/external_begin.hpp>
#include <X11/Xlib.h>
#include <X11/extensions/XI2.h>
#include <X11/extensions/XInput2.h>
#include <fcppt/config/external_end.hpp>


XKeyEvent
sge::x11input::focus::translate_event(
	XIDeviceEvent const &_event
)
{
	XKeyEvent const xev =
	{
		[](
			int const _type
		)
		{
			switch(
				_type
			)
			{
			case XI_KeyPress:
				return
					KeyPress;
			case XI_KeyRelease:
				return
					KeyRelease;
			}

			FCPPT_ASSERT_UNREACHABLE;
		}(
			_event.evtype
		),
		_event.serial,
		_event.send_event,
		_event.display,
		_event.event,
		_event.root,
		_event.child,
		_event.time,
		fcppt::cast::float_to_int<
			int
		>(
			_event.event_x
		),
		fcppt::cast::float_to_int<
			int
		>(
			_event.event_y
		),
		fcppt::cast::float_to_int<
			int
		>(
			_event.root_x
		),
		fcppt::cast::float_to_int<
			int
		>(
			_event.root_y
		),
		fcppt::cast::to_unsigned(
			_event.mods.effective
			|
			((_event.group.effective & 0x3) << 13)
		),
		fcppt::cast::to_unsigned(
			_event.detail
		),
		True // same_screen?
	};

	return
		xev;
}
