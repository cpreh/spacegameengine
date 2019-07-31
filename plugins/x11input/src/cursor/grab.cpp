//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/input/exception.hpp>
#include <sge/x11input/cursor/grab.hpp>
#include <sge/x11input/cursor/grab_error_to_string.hpp>
#include <sge/x11input/device/id.hpp>
#include <awl/backends/x11/display.hpp>
#include <awl/backends/x11/cursor/object.hpp>
#include <awl/backends/x11/window/base.hpp>
#include <fcppt/text.hpp>
#include <fcppt/config/external_begin.hpp>
#include <X11/X.h>
#include <X11/extensions/XInput2.h>
#include <fcppt/config/external_end.hpp>


sge::x11input::cursor::grab::grab(
	awl::backends::x11::window::base const &_window,
	sge::x11input::device::id const _id,
	awl::backends::x11::cursor::object const &_cursor
)
:
	window_(
		_window
	),
	id_(
		_id
	)
{
	XIEventMask mask{
		id_.get(),
		0,
		nullptr
	};

	Status const ret(
		::XIGrabDevice(
			_window.display().get(),
			_id.get(),
			_window.get(),
			CurrentTime,
			_cursor.get(),
			GrabModeAsync,
			GrabModeAsync,
			True,
			&mask
		)
	);


	if(
		ret
		!=
		GrabSuccess
	)
		throw
			sge::input::exception{
				FCPPT_TEXT("X11 grab failed with code ")
				+
				sge::x11input::cursor::grab_error_to_string(
					ret
				)
			};
}

sge::x11input::cursor::grab::~grab()
{
	::XIUngrabDevice(
		window_.display().get(),
		id_.get(),
		CurrentTime
	);
}
