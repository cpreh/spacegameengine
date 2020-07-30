//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/input/cursor/button_code.hpp>
#include <sge/sdlinput/cursor/translate_button_code.hpp>
#include <fcppt/config/external_begin.hpp>
#include <SDL_mouse.h>
#include <cstdint>
#include <fcppt/config/external_end.hpp>


sge::input::cursor::button_code
sge::sdlinput::cursor::translate_button_code(
	std::uint8_t const _code
)
{
	switch(
		_code
	)
	{
	case SDL_BUTTON_LEFT:
		return
			sge::input::cursor::button_code::left;
	case SDL_BUTTON_MIDDLE:
		return
			sge::input::cursor::button_code::middle;
	case SDL_BUTTON_RIGHT:
		return
			sge::input::cursor::button_code::right;
	default:
		break;
	}

	return
		sge::input::cursor::button_code::unknown;
}
