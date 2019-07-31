//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/input/focus/key.hpp>
#include <sge/input/focus/shared_ptr.hpp>
#include <sge/input/focus/event/base.hpp>
#include <sge/input/focus/event/key.hpp>
#include <sge/input/key/pressed.hpp>


sge::input::focus::event::key::key(
	sge::input::focus::shared_ptr const _focus,
	sge::input::focus::key const &_key,
	sge::input::key::pressed const _pressed
)
:
	sge::input::focus::event::base{
		_focus
	},
	key_{
		_key
	},
	pressed_{
		_pressed
	}
{
}

sge::input::focus::event::key::~key()
{
}

sge::input::focus::key const &
sge::input::focus::event::key::get() const
{
	return
		key_;
}

bool
sge::input::focus::event::key::pressed() const
{
	return
		pressed_.get();
}
