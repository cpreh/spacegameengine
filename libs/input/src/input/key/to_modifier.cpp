//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/input/key/code.hpp>
#include <sge/input/key/is_alt.hpp>
#include <sge/input/key/is_control.hpp>
#include <sge/input/key/is_shift.hpp>
#include <sge/input/key/modifier.hpp>
#include <sge/input/key/optional_modifier.hpp>
#include <sge/input/key/to_modifier.hpp>


sge::input::key::optional_modifier
sge::input::key::to_modifier(
	sge::input::key::code const _code
)
{
	if(
		sge::input::key::is_control(
			_code
		)
	)
	{
		return
			sge::input::key::optional_modifier(
				sge::input::key::modifier::control
			);
	}

	if(
		sge::input::key::is_alt(
			_code
		)
	)
	{
		return
			sge::input::key::optional_modifier(
				sge::input::key::modifier::alt
			);
	}

	if(
		sge::input::key::is_shift(
			_code
		)
	)
	{
		return
			sge::input::key::optional_modifier(
				sge::input::key::modifier::shift
			);
	}

	return
		sge::input::key::optional_modifier();
}
