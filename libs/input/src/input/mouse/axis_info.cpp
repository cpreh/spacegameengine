//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/input/mouse/axis_code.hpp>
#include <sge/input/mouse/axis_info.hpp>
#include <fcppt/optional_string.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>


sge::input::mouse::axis_info::axis_info(
	sge::input::mouse::axis_code const _code,
	fcppt::optional_string &&_name
)
:
	code_(
		_code
	),
	name_(
		std::move(
			_name
		)
	)
{
}

sge::input::mouse::axis_code
sge::input::mouse::axis_info::code() const
{
	return
		code_;
}

fcppt::optional_string const &
sge::input::mouse::axis_info::name() const
{
	return
		name_;
}
