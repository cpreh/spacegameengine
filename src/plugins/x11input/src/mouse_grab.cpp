/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2010 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include "../mouse_grab.hpp"
#include "../handle_grab.hpp"
#include "../cursor.hpp"
#include <X11/Xlib.h>
#include <sge/time/sleep.hpp>
#include <sge/time/second.hpp>
#include <awl/backends/x11/window_instance.hpp>
#include <awl/backends/x11/display.hpp>

sge::x11input::mouse_grab::mouse_grab(
	awl::backends::x11::window_instance_ptr const _window,
	x11input::cursor const &_cursor
)
:
	window_(_window)
{
	while(
		!x11input::handle_grab(
			::XGrabPointer(
				window_->display()->get(),
				window_->get(),
				True,
				PointerMotionMask
				| ButtonPressMask
				| ButtonReleaseMask,
				GrabModeAsync,
				GrabModeAsync,
				window_->get(),
				_cursor.get(),
				CurrentTime
			)
		)
	)
		sge::time::sleep(
			sge::time::second(
				1
			)
		);
}

sge::x11input::mouse_grab::~mouse_grab()
{
	::XUngrabPointer(
		window_->display()->get(),
		CurrentTime
	);
}
