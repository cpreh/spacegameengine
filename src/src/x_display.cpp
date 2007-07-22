/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006  Carl Philipp Reh (sefi@s-e-f-i.de)

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/


#include "../types.hpp"
#ifdef SGE_LINUX_PLATFORM
#include "../exception.hpp"
#include "../x_display.hpp"
	
sge::x_display::x_display()
: d(XOpenDisplay(0))
{
	if(!d)
		throw exception("XOpenDisplay failed or dsp is 0");
}

sge::x_display::~x_display()
{
	XCloseDisplay(d);
}

Display* sge::x_display::get() const
{
	return d;
}
#endif
