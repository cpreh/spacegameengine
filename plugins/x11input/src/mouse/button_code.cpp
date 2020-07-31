//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/input/mouse/button_code.hpp>
#include <sge/x11input/mouse/button_code.hpp>
#include <fcppt/optional_string.hpp>
#include <fcppt/string.hpp>
#include <fcppt/text.hpp>
#include <fcppt/optional/maybe.hpp>


sge::input::mouse::button_code
sge::x11input::mouse::button_code(
	fcppt::optional_string const &_info
)
{
	return
		fcppt::optional::maybe(
			_info,
			[]{
				return
					sge::input::mouse::button_code::unknown;
			},
			[](
				fcppt::string const &_name
			)
			{
				if(
					_name == FCPPT_TEXT("Button Left")
				)
				{
					return
						sge::input::mouse::button_code::left;
				}

				if(
					_name == FCPPT_TEXT("Button Right")
				)
				{
					return
						sge::input::mouse::button_code::right;
				}

				if(
					_name == FCPPT_TEXT("Button Middle")
				)
				{
					return
						sge::input::mouse::button_code::middle;
				}

				return
					sge::input::mouse::button_code::unknown;
			}
		);
}
