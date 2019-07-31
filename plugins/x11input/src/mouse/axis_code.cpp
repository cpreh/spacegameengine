//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/input/mouse/axis_code.hpp>
#include <sge/x11input/mouse/axis_code.hpp>
#include <fcppt/optional_string.hpp>
#include <fcppt/string.hpp>
#include <fcppt/text.hpp>
#include <fcppt/optional/maybe.hpp>


sge::input::mouse::axis_code
sge::x11input::mouse::axis_code(
	fcppt::optional_string const &_info
)
{
	return
		fcppt::optional::maybe(
			_info,
			[]
			{
				return
					sge::input::mouse::axis_code::unknown;
			},
			[](
				fcppt::string const &_name
			)
			{
				if(
					_name == FCPPT_TEXT("Rel X")
					||
					_name == FCPPT_TEXT("Abs X")
				)
					return
						sge::input::mouse::axis_code::x;

				if(
					_name == FCPPT_TEXT("Rel Y")
					||
					_name == FCPPT_TEXT("Abs Y")
				)
					return
						sge::input::mouse::axis_code::y;

				if(
					_name == FCPPT_TEXT("Rel Z")
					||
					_name == FCPPT_TEXT("Abs Z")
				)
					return
						sge::input::mouse::axis_code::wheel;

				return
					sge::input::mouse::axis_code::unknown;
			}
		);
}
