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


#include <sge/x11input/cursor/pixmap.hpp>
#include <sge/x11input/pixmap.hpp>
#include <sge/input/exception.hpp>
#include <awl/backends/x11/display.hpp>
#include <fcppt/text.hpp>
#include <fcppt/config/external_begin.hpp>
#include <X11/Xlib.h>
#include <fcppt/config/external_end.hpp>

namespace
{

XColor black = { 0, 0, 0, 0, 0, 0 };

}

sge::x11input::cursor::pixmap::pixmap(
	awl::backends::x11::display &_display,
	x11input::pixmap const &_pixmap
)
:
 	display_(_display),
	cursor_(
		cursor::image(
			::XCreatePixmapCursor(
				display_.get(),
				_pixmap.get(),
				_pixmap.get(),
				&black,
				&black,
				0,
				0
			)
		)
	)
{
	if(
		cursor_.get() == None
	)
		throw sge::input::exception(
			FCPPT_TEXT("XCreatePixmapCursor() failed!")
		);
}

sge::x11input::cursor::pixmap::~pixmap()
{
	::XFreeCursor(
		display_.get(),
		cursor_.get()
	);
}

sge::x11input::cursor::image const
sge::x11input::cursor::pixmap::get() const
{
	return cursor_;
}
