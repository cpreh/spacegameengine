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


#include <sge/x11input/send_init_event.hpp>
#include <awl/backends/x11/atom.hpp>
#include <awl/backends/x11/display.hpp>
#include <awl/backends/x11/window/instance.hpp>
#include <awl/backends/x11/window/event/mask.hpp>
#include <awl/backends/x11/window/event/object.hpp>
#include <awl/backends/x11/window/event/send.hpp>
#include <fcppt/config/external_begin.hpp>
#include <X11/Xlib.h>
#include <fcppt/config/external_end.hpp>


void
sge::x11input::send_init_event(
	awl::backends::x11::window::instance const &_window,
	awl::backends::x11::atom const _atom
)
{
	XClientMessageEvent client_message;

	client_message.type = ClientMessage;
	client_message.display = _window.display().get();
	client_message.window = _window.get();
	client_message.message_type = _atom.get();
	client_message.format = 8; // dont' care about the format

	XEvent event;

	event.type = ClientMessage;
	event.xclient = client_message;

	awl::backends::x11::window::event::send(
		_window,
		awl::backends::x11::window::event::mask(
			NoEventMask
		),
		awl::backends::x11::window::event::object(
			event
		)
	);
}
