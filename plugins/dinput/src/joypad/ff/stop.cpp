//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/dinput/di.hpp>
#include <sge/dinput/joypad/ff/stop.hpp>
#include <sge/input/exception.hpp>
#include <fcppt/text.hpp>


void
sge::dinput::joypad::ff::stop(
	IDirectInputEffect &_effect
)
{
	if(
		_effect.Stop()
		!=
		DI_OK
	)
		throw
			sge::input::exception{
				FCPPT_TEXT("Stopping an effect failed")
			};
}
