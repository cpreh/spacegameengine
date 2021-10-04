//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/input/key/code.hpp>
#include <sge/input/key/code_to_digit.hpp>
#include <sge/input/key/digit.hpp>
#include <sge/input/key/optional_digit.hpp>
#include <fcppt/preprocessor/disable_clang_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>


sge::input::key::optional_digit
sge::input::key::code_to_digit(
	sge::input::key::code const _code
)
{
#define CONVERT_KEYCODE_TO_DIGIT(\
	num\
) \
case sge::input::key::code::_ ## num: \
	return \
		sge::input::key::optional_digit(\
			sge::input::key::digit(\
				num ## u \
			) \
		)

FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_CLANG_WARNING(-Wswitch-enum)

	switch(
		_code
	)
	{
	CONVERT_KEYCODE_TO_DIGIT(0);
	CONVERT_KEYCODE_TO_DIGIT(1);
	CONVERT_KEYCODE_TO_DIGIT(2);
	CONVERT_KEYCODE_TO_DIGIT(3);
	CONVERT_KEYCODE_TO_DIGIT(4);
	CONVERT_KEYCODE_TO_DIGIT(5);
	CONVERT_KEYCODE_TO_DIGIT(6);
	CONVERT_KEYCODE_TO_DIGIT(7);
	CONVERT_KEYCODE_TO_DIGIT(8);
	CONVERT_KEYCODE_TO_DIGIT(9);
	default:
		return
			{};
	}

FCPPT_PP_POP_WARNING

}
