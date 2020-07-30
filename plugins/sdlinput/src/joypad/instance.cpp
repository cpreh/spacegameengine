//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/input/exception.hpp>
#include <sge/sdlinput/joypad/device_id.hpp>
#include <sge/sdlinput/joypad/instance.hpp>
#include <fcppt/text.hpp>
#include <fcppt/config/external_begin.hpp>
#include <SDL_joystick.h>
#include <fcppt/config/external_end.hpp>


sge::sdlinput::joypad::instance::instance(
	sge::sdlinput::joypad::device_id const _id
)
:
	impl_{
		SDL_JoystickOpen(
			_id.get()
		)
	}
{
	if(
		impl_
		==
		nullptr
	)
	{
		throw
			sge::input::exception{
				FCPPT_TEXT("SDL_JoystickOpen failed!")
			};
	}
}

sge::sdlinput::joypad::instance::~instance()
{
	SDL_JoystickClose(
		this->impl_
	);
}

SDL_Joystick &
sge::sdlinput::joypad::instance::get() const
{
	return
		*this->impl_;
}
