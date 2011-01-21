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


#include "../cursor_define.hpp"
#include <sge/input/exception.hpp>
#include <awl/backends/x11/window/instance.hpp>
#include <awl/backends/x11/display.hpp>
#include <fcppt/text.hpp>
#include <X11/extensions/XInput2.h>

sge::x11input::cursor_define::cursor_define(
	awl::backends::x11::window::instance_ptr const _window,
	device::id const &_id
)
:
	window_(_window),
	id_(_id),
	pixmap_(
		_window
	),
	pixmap_cursor_(
		_window->display(),
		pixmap_.get()
	)
{
	if(
		::XIDefineCursor(
			_window->display()->get(),
			_id.get(),
			_window->get(),
			pixmap_cursor_.get()
		)
		!= Success
	)
		throw sge::input::exception(
			FCPPT_TEXT("XIDefineCursor failed!")
		);
}

sge::x11input::cursor_define::~cursor_define()
{
	::XIUndefineCursor(
		window_->display()->get(),
		id_.get(),
		window_->get()
	);
}
