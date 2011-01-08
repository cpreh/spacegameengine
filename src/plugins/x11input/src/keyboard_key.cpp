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
#include <sge/input/keyboard/key.hpp>
#include <awl/backends/x11/display.hpp>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <limits>
//#include <X11/XKBlib.h>

sge::input::keyboard::key const
sge::x11input::keyboard_key(
	awl::backends::x11::display_ptr const _display,
	int const _key_code
)
{

	XComposeStatus state;

	KeySym key_sym;

	// HACK HACK
	XKeyEvent xev =
	{
		KeyPress,
		0,
		False,
		_display->get(),
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0u,
		_key_code,
		False
	};

	int const num_chars(
		XLookupString(
			const_cast<
				XKeyEvent *
			>(
				&xev
			),
			0,
			0,
			&key_sym,
			&state
		)
	);

	// xev does it this way
	char const char_code(
		key_sym	
		>
		static_cast<
			KeySym
		>(
			std::numeric_limits<char>::max()
		)
		?
			static_cast<char>(0)
		:
			static_cast<char>(key_sym)
	);

	return
		input::keyboard::key(
			x11input::translate_key_code(
				key_sym
			),
			char_code
		);

#if 0
	KeySym const key_sym(
		::XkbKeycodeToKeysym(
			_display->get(),
			_key_code,
			0,
			0 // TODO!
		)
	);

	return
		input::keyboard::key(
			x11input::translate_key_code(
				key_sym
			),
			0//char_code // TODO: translate this!
		);
	#endif
}
