/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2009 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include "../keyboard.hpp"
#include "../keyboard_grab.hpp"
#include "../keyboard_keys.hpp"
#include <X11/Xlib.h>
#include <sge/x11/window.hpp>
#include <sge/x11/display.hpp>
#include <sge/input/key_type.hpp>
#include <sge/input/key_pair.hpp>
#include <tr1/functional>

sge::x11input::keyboard::keyboard(
	x11::window_ptr const wnd,
	input::callback const &callback,
	input::repeat_callback const &repeat_callback
)
:
	wnd(wnd),
	callback(callback),
	repeat_callback(repeat_callback),
	need_grab(wnd->fullscreen())
{
	connections.connect(
		wnd->register_callback(
			KeyPress,
			std::tr1::bind(
				&keyboard::on_key_event,
				this,
				std::tr1::placeholders::_1
			)
		)
	);

	connections.connect(
		wnd->register_callback(
			KeyRelease,
			std::tr1::bind(
				&keyboard::on_key_event,
				this,
				std::tr1::placeholders::_1
			)
		)
	);
}

void sge::x11input::keyboard::grab()
{
	if(need_grab)
		grab_.reset(
			new keyboard_grab(
				wnd
			)
		);
}

void sge::x11input::keyboard::ungrab()
{
	grab_.reset();
}

void sge::x11input::keyboard::on_key_event(
	XEvent const &xev)
{
	XKeyEvent const &key_event(xev.xkey);

	input::key_type const key(
		keyboard_key(
			key_event
		)
	);

	// check for repeated key (thanks to SDL)
	if(xev.type == KeyRelease && XPending(wnd->display()->get()))
	{
		XEvent peek;
		XPeekEvent(wnd->display()->get(), &peek);
		if(
			peek.type == KeyPress &&
			peek.xkey.keycode == xev.xkey.keycode &&
			(peek.xkey.time - xev.xkey.time) < 2
		)
		{
			XNextEvent(wnd->display()->get(), &peek);
			repeat_callback(key);
			return;
		}
	}

	callback(
		input::key_pair(
			key,
			xev.type == KeyRelease ? 0 : 1
		)
	);
}
