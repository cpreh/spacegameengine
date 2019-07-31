//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/input/mouse/button_code.hpp>
#include <sge/input/mouse/button_info.hpp>
#include <fcppt/optional_string.hpp>


sge::input::mouse::button_info::button_info(
	sge::input::mouse::button_code const _code,
	fcppt::optional_string const &_name
)
:
	code_(
		_code
	),
	name_(
		_name
	)
{
}

sge::input::mouse::button_code
sge::input::mouse::button_info::code() const
{
	return
		code_;
}

fcppt::optional_string const &
sge::input::mouse::button_info::name() const
{
	return
		name_;
}
