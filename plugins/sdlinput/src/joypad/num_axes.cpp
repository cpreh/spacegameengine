//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/input/info/id.hpp>
#include <sge/sdlinput/joypad/num_axes.hpp>
#include <fcppt/cast/to_unsigned.hpp>
#include <fcppt/config/external_begin.hpp>
#include <SDL_joystick.h>
#include <fcppt/config/external_end.hpp>


sge::input::info::id
sge::sdlinput::joypad::num_axes(
	SDL_Joystick &_joystick
)
{
	return
		fcppt::cast::to_unsigned(
			SDL_JoystickNumAxes(
				&_joystick
			)
		);
}
