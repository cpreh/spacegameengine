//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/input/keyboard/shared_ptr.hpp>
#include <sge/input/keyboard/event/base.hpp>
#include <sge/input/keyboard/event/discover.hpp>


sge::input::keyboard::event::discover::discover(
	sge::input::keyboard::shared_ptr const _keyboard
)
:
	sge::input::keyboard::event::base{
		_keyboard
	}
{
}

sge::input::keyboard::event::discover::~discover()
{
}
