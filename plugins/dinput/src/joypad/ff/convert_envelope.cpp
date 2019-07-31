//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/dinput/di.hpp>
#include <sge/dinput/joypad/ff/convert_duration.hpp>
#include <sge/dinput/joypad/ff/convert_envelope.hpp>
#include <sge/input/joypad/ff/envelope.hpp>
#include <fcppt/cast/size.hpp>


DIENVELOPE
sge::dinput::joypad::ff::convert_envelope(
	sge::input::joypad::ff::envelope const &_envelope
)
{
	return
		DIENVELOPE{
			sizeof(
				DIENVELOPE
			),
			fcppt::cast::size<
				DWORD
			>(
				_envelope.attack_level().get()
			),
			sge::dinput::joypad::ff::convert_duration(
				_envelope.attack_time().get()
			),
			fcppt::cast::size<
				DWORD
			>(
				_envelope.fade_level().get()
			),
			sge::dinput::joypad::ff::convert_duration(
				_envelope.fade_time().get()
			)
		};
}
