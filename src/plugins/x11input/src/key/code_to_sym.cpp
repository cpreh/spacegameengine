/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2015 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#include <sge/x11input/key/code_to_sym.hpp>
#include <awl/backends/x11/display.hpp>
#include <fcppt/config/external_begin.hpp>
#include <X11/X.h>
#include <X11/XKBlib.h>
#include <fcppt/config/external_end.hpp>


KeySym
sge::x11input::key::code_to_sym(
	awl::backends::x11::display &_display,
	int const _key_code
)
{
	// The XI2 event passes the key code as an int, but XKB requires a
	// KeyCode (which is unsigned char) or an unsigned int.
	return
		::XkbKeycodeToKeysym(
			_display.get(),
#if NeedWidePrototypes
			static_cast<
				unsigned
			>(
				_key_code
			),
#else
			static_cast<
				KeyCode
			>(
				_key_code
			),
#endif
			0,
			0
		);
}
