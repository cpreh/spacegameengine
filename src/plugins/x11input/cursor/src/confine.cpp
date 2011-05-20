/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2011 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include "../confine.hpp"
#include <sge/x11input/config.hpp>
#include <awl/backends/x11/window/instance.hpp>
#include <awl/backends/x11/display.hpp>
#if defined(SGE_X11INPUT_HAVE_XI_2_1)
#include <sge/input/exception.hpp>
#include <X11/extensions/XInput2.h>
#include <fcppt/text.hpp>
#else
#include <sge/time/sleep.hpp>
#include <sge/time/second.hpp>
#include <X11/Xlib.h>
#endif

sge::x11input::cursor::confine::confine(
	awl::backends::x11::window::instance &_window,
	device::id const &_id
)
:
	window_(_window)
#if defined(SGE_X11INPUT_HAVE_XI_2_1)
	,
	id_(_id)
#endif
{
#if defined(SGE_X11INPUT_HAVE_XI_2_1)
	unsigned char raw_data[4] = {0};

	XISetMask(
		raw_data,
		XI_Motion
	);

	XISetMask(
		raw_data,
		XI_ButtonPress
	);

	XISetMask(
		raw_data,
		XI_ButtonRelease
	);

	XIEventMask mask =
	{
		id_.get(),
		4,
		raw_data
	};

	if(
		::XIGrabDeviceWithConfine(
			_window.display().get(),
			_id.get(),
			_window.get(),
			_window.get(),
			CurrentTime,
			None,//_window->display()->get()->cursor,
			GrabModeAsync,
			GrabModeAsync,
			True,
			&mask//,
			//num_modifiers_,
			//&modifiers_
		)
		== -1
	)
	// TODO: do we have to sleep here on some return values as well?
		throw sge::input::exception(
			FCPPT_TEXT("XIGrabEnter failed!")
		);
#else
	while(
		::XGrabPointer(
			window_.display().get(),
			window_.get(),
			True,
			0u,
			GrabModeAsync,
			GrabModeAsync,
			window_.get(),
			None,
			CurrentTime
		)
		!= GrabSuccess
	)
		sge::time::sleep(
			sge::time::second(
				1
			)
		);
#endif
}

sge::x11input::cursor::confine::~confine()
{
#if defined(SGE_X11INPUT_HAVE_XI_2_1)
	::XIUngrabDevice(
		window_.display().get(),
		id_.get(),
		CurrentTime
	);
#else
	::XUngrabPointer(
		window_.display().get(),
		CurrentTime
	);
#endif
}
