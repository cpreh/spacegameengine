//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/input/exception.hpp>
#include <sge/sdlinput/joypad/instance_id.hpp>
#include <fcppt/text.hpp>
#include <fcppt/config/external_begin.hpp>
#include <SDL_joystick.h>
#include <fcppt/config/external_end.hpp>


SDL_JoystickID
sge::sdlinput::joypad::instance_id(
	SDL_Joystick &_joystick
)
{
	SDL_JoystickID const result{
		SDL_JoystickInstanceID(
			&_joystick
		)
	};

	if(
		result
		==
		-1
	)
	{
		throw
			sge::input::exception{
				FCPPT_TEXT("SDL_JoystickInstanceID failed!")
			};
	}

	return
		result;
}
