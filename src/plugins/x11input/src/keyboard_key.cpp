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


#include "../keyboard_key.hpp"
#include "../translate_key_code.hpp"
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <sge/input/keyboard/key.hpp>
#include <limits>

sge::input::key_type const
sge::x11input::keyboard_key(
	XKeyEvent const &_xev
)
{
	XComposeStatus state;

	KeySym ks;

	int const num_chars(
		XLookupString(
			const_cast<
				XKeyEvent *
			>(
				&_xev
			),
			0,
			0,
			&ks,
			&state
		)
	);

	// xev does it this way
	char const char_code(
		ks
		>
		static_cast<
			KeySym
		>(
			std::numeric_limits<char>::max()
		)
		?
			static_cast<char>(0)
		:
			static_cast<char>(ks)
	);

	return
		input::keyboard::key(
			x11input::translate_key_code(
				ks
			)	
			char_code // TODO: translate this!
		);
}
