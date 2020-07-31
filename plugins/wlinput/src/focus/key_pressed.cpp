//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/input/key/pressed.hpp>
#include <sge/wlinput/focus/key_pressed.hpp>
#include <fcppt/assert/unreachable.hpp>
#include <fcppt/config/external_begin.hpp>
#include <wayland-client-protocol.h>
#include <cstdint>
#include <fcppt/config/external_end.hpp>


sge::input::key::pressed
sge::wlinput::focus::key_pressed(
	std::uint32_t const _value
)
{
	switch(
		_value
	)
	{
	case WL_KEYBOARD_KEY_STATE_RELEASED:
		return
			sge::input::key::pressed{
				false
			};
	case WL_KEYBOARD_KEY_STATE_PRESSED:
		return
			sge::input::key::pressed{
				true
			};
	default:
		break;
	}

	FCPPT_ASSERT_UNREACHABLE;
}
