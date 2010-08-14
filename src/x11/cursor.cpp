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


#include <X11/Xlib.h>
#include <sge/x11/cursor.hpp>
#include <sge/x11/display.hpp>
#include <sge/exception.hpp>
#include <fcppt/text.hpp>

sge::x11::cursor::cursor(
	display_ptr const dsp,
	Pixmap const pixmap,
	XColor color)
 :
 	dsp(dsp),
	cursor_(
		XCreatePixmapCursor(
			dsp->get(),
			pixmap,
			pixmap,
			&color,
			&color,
			0,
			0))
{
	if(get() == None)
		throw exception(
			FCPPT_TEXT("XCreatePixmapCursor() failed!"));
}

sge::x11::cursor::~cursor()
{
	XFreeCursor(
		dsp->get(),
		get());
}

Cursor sge::x11::cursor::get() const
{
	return cursor_;
}
