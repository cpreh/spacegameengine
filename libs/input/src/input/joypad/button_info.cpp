//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/input/joypad/button_info.hpp>
#include <fcppt/optional_string.hpp>


sge::input::joypad::button_info::button_info(
	fcppt::optional_string const &_name
)
:
	name_(
		_name
	)
{
}

fcppt::optional_string const &
sge::input::joypad::button_info::name() const
{
	return
		name_;
}
