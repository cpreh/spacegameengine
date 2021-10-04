//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_WLINPUT_CURSOR_BUTTON_STATE_HPP_INCLUDED
#define SGE_WLINPUT_CURSOR_BUTTON_STATE_HPP_INCLUDED

#include <sge/input/cursor/button_pressed.hpp>
#include <fcppt/config/external_begin.hpp>
#include <cstdint>
#include <fcppt/config/external_end.hpp>


namespace sge::wlinput::cursor
{

sge::input::cursor::button_pressed
button_state(
	std::uint32_t
);

}

#endif
