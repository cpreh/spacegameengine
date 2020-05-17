//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/input/event_base.hpp>
#include <sge/input/keyboard/device.hpp>
#include <sge/input/keyboard/shared_ptr.hpp>
#include <sge/input/keyboard/event/base.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>


sge::input::keyboard::event::base::base(
	sge::input::keyboard::shared_ptr _keyboard
)
:
	sge::input::event_base{
		_keyboard->window()
	},
	keyboard_{
		std::move(
			_keyboard
		)
	}
{
}

sge::input::keyboard::event::base::~base()
= default;

sge::input::keyboard::shared_ptr const &
sge::input::keyboard::event::base::keyboard() const
{
	return
		keyboard_;
}
