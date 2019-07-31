//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


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
	return
		XKeyEvent{
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
}
