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


#include <X11/Xlib.h>
#include "../pixmap_cursor.hpp"
#include <sge/input/exception.hpp>
#include <awl/backends/x11/display.hpp>
#include <fcppt/text.hpp>

sge::x11input::pixmap_cursor::pixmap_cursor(
	awl::backends::x11::display_ptr const _display,
	Pixmap const _pixmap,
	XColor _color
)
:
 	display_(_display),
	cursor_(
		::XCreatePixmapCursor(
			display_->get(),
			_pixmap,
			_pixmap,
			&_color,
			&_color,
			0,
			0
		)
	)
{
	if(
		cursor_ == None
	)
		throw sge::input::exception(
			FCPPT_TEXT("XCreatePixmapCursor() failed!")
		);
}

sge::x11input::pixmap_cursor::~pixmap_cursor()
{
	::XFreeCursor(
		display_->get(),
		get()
	);
}

Cursor
sge::x11input::pixmap_cursor::get() const
{
	return cursor_;
}
