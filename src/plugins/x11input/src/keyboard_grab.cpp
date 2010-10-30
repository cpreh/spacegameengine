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


#include "../keyboard_grab.hpp"
#include "../handle_grab.hpp"
#include <X11/Xlib.h>
#include <sge/input/exception.hpp>
#include <awl/backends/x11/window_instance.hpp>
#include <awl/backends/x11/display.hpp>
#include <fcppt/text.hpp>

sge::x11input::keyboard_grab::keyboard_grab(
	awl::backends::x11::window_instance_ptr const _window
)
:
	window_(_window)
{
	if(
		x11input::handle_grab(
			::XGrabKeyboard(
				window_->display()->get(),
				window_->get(),
				True,
				GrabModeAsync,
				GrabModeAsync,
				CurrentTime
			)
		)
	)
		throw sge::input::exception(
			FCPPT_TEXT("Keyboard grab failed!")
		);
}

sge::x11input::keyboard_grab::~keyboard_grab()
{
	::XUngrabKeyboard(
		window_->display()->get(),
		CurrentTime
	);
}
