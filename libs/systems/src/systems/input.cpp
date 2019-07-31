//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/systems/cursor_option_field.hpp>
#include <sge/systems/input.hpp>


sge::systems::input::input(
	sge::systems::cursor_option_field const &_cursor_options
)
:
	cursor_options_{
		_cursor_options
	}
{
}

sge::systems::cursor_option_field const &
sge::systems::input::cursor_options() const
{
	return
		cursor_options_;
}
