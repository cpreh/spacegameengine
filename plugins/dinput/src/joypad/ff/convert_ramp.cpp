//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/dinput/di.hpp>
#include <sge/dinput/joypad/ff/convert_ramp.hpp>
#include <sge/input/joypad/ff/ramp.hpp>
#include <fcppt/cast/size.hpp>


DIRAMPFORCE
sge::dinput::joypad::ff::convert_ramp(
	sge::input::joypad::ff::ramp const &_ramp
)
{
	return
		DIRAMPFORCE{
			fcppt::cast::size<
				LONG
			>(
				_ramp.start_magnitude().get()
			),
			fcppt::cast::size<
				LONG
			>(
				_ramp.end_magnitude().get()
			)
		};
}
