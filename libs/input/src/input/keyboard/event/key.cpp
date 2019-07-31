//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/input/key/pressed.hpp>
#include <sge/input/keyboard/key.hpp>
#include <sge/input/keyboard/shared_ptr.hpp>
#include <sge/input/keyboard/event/base.hpp>
#include <sge/input/keyboard/event/key.hpp>


sge::input::keyboard::event::key::key(
	sge::input::keyboard::shared_ptr const _keyboard,
	sge::input::keyboard::key const &_key,
	sge::input::key::pressed const _pressed
)
:
	sge::input::keyboard::event::base{
		_keyboard
	},
	key_{
		_key
	},
	pressed_{
		_pressed
	}
{
}

sge::input::keyboard::event::key::~key()
{
}

sge::input::keyboard::key const &
sge::input::keyboard::event::key::get() const
{
	return
		key_;
}

bool
sge::input::keyboard::event::key::pressed() const
{
	return
		pressed_.get();
}
