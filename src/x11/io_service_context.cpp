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


#include <sge/x11/io_service_context.hpp>
#include <sge/x11/window.hpp>
#include <sge/x11/display.hpp>
#include <sge/mainloop/io_service.hpp>
#include <fcppt/tr1/functional.hpp>
#include <X11/Xlibint.h>

sge::x11::io_service_context::io_service_context(	
	mainloop::io_service_ptr const _io_service,
	x11::display_ptr const _display,
	x11::window_ptr const _window
)
:
	window_(_window),
	dispatcher_(
		_io_service->create_dispatcher(
			_display->get()->fd,
			std::tr1::bind(
				&io_service_context::callback,
				this
			)
		)
	)
{
}

void
sge::x11::io_service_context::callback()
{
	window_->dispatch();
}
