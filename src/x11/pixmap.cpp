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



#include <X11/Xlib.h>
#include <sge/x11/pixmap.hpp>
#include <sge/x11/display.hpp>
#include <sge/exception.hpp>
#include <sge/text.hpp>

namespace
{

char const bm_no_data[] = { 0,0,0,0, 0,0,0,0 };

}

sge::x11::pixmap::pixmap(
	display_ptr const dsp,
	Window const wnd)
 :
 	dsp(dsp),
	pixmap_(
		XCreateBitmapFromData(
			dsp->get(),
			wnd,
			bm_no_data,
			8,
			8))
{
	if(get() == None)
		throw exception(
			SGE_TEXT("XCreateBitmapFromData() failed!"));
}

sge::x11::pixmap::~pixmap()
{
	XFreePixmap(
		dsp->get(),
		get());
}

Pixmap sge::x11::pixmap::get() const
{
	return pixmap_;
}
