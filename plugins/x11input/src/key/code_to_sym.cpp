//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/x11input/key/code.hpp>
#include <sge/x11input/key/code_to_sym.hpp>
#include <awl/backends/x11/display.hpp>
#include <fcppt/config/external_begin.hpp>
#include <X11/X.h>
#include <X11/XKBlib.h>
#include <fcppt/config/external_end.hpp>


KeySym
sge::x11input::key::code_to_sym(
	awl::backends::x11::display const &_display,
	sge::x11input::key::code const _key_code
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
				_key_code.get()
			),
#else
			static_cast<
				KeyCode
			>(
				_key_code.get()
			),
#endif
			0,
			0
		);
}
