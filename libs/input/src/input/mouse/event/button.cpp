//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/input/mouse/button.hpp>
#include <sge/input/mouse/button_code.hpp>
#include <sge/input/mouse/button_pressed.hpp>
#include <sge/input/mouse/shared_ptr.hpp>
#include <sge/input/mouse/event/base.hpp>
#include <sge/input/mouse/event/button.hpp>


sge::input::mouse::event::button::button(
	sge::input::mouse::shared_ptr const _mouse,
	sge::input::mouse::button const &_button,
	sge::input::mouse::button_pressed const _pressed
)
:
	sge::input::mouse::event::base{
		_mouse
	},
	button_{
		_button
	},
	pressed_{
		_pressed
	}
{
}

sge::input::mouse::event::button::~button()
{
}

sge::input::mouse::button_code
sge::input::mouse::event::button::button_code() const
{
	return
		button_.code();
}

sge::input::mouse::button const &
sge::input::mouse::event::button::get() const
{
	return
		button_;
}

bool
sge::input::mouse::event::button::pressed() const
{
	return
		pressed_.get();
}
