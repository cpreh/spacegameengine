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


#include "../use_xkb.hpp"
#include <awl/backends/x11/display.hpp>
#include <X11/XKBlib.h>

bool
sge::x11input::use_xkb(
	awl::backends::x11::display_ptr const _display
)
{
	// TODO: do we have to initialize this?
	int major = 1, minor = 0;

	return
		::XkbUseExtension(
			_display->get(),
			&major,
			&minor
		)
		== True;
}
