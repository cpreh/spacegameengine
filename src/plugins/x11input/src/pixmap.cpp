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


#include "../pixmap.hpp"
#include <awl/backends/x11/window/instance.hpp>
#include <awl/backends/x11/display.hpp>
#include <sge/input/exception.hpp>
#include <fcppt/text.hpp>
#include <fcppt/config/external_begin.hpp>
#include <X11/Xlib.h>
#include <fcppt/config/external_end.hpp>

namespace
{

char const bm_no_data[] = { 0,0,0,0, 0,0,0,0 };

}

sge::x11input::pixmap::pixmap(
	awl::backends::x11::window::instance &_window
)
:
 	display_(
		_window.display()
	),
	pixmap_(
		::XCreateBitmapFromData(
			display_.get(),
			_window.get(),
			::bm_no_data,
			8,
			8
		)
	)
{
	if(
		pixmap_ == None
	)
		throw sge::input::exception(
			FCPPT_TEXT("XCreateBitmapFromData() failed!")
		);
}

sge::x11input::pixmap::~pixmap()
{
	::XFreePixmap(
		display_.get(),
		this->get()
	);
}

Pixmap
sge::x11input::pixmap::get() const
{
	return pixmap_;
}
