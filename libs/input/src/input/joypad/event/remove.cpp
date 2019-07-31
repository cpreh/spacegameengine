//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/input/joypad/shared_ptr.hpp>
#include <sge/input/joypad/event/base.hpp>
#include <sge/input/joypad/event/remove.hpp>


sge::input::joypad::event::remove::remove(
	sge::input::joypad::shared_ptr const _joypad
)
:
	sge::input::joypad::event::base{
		_joypad
	}
{
}

sge::input::joypad::event::remove::~remove()
{
}
