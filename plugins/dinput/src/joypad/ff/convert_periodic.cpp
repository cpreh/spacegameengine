//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/dinput/di.hpp>
#include <sge/dinput/joypad/ff/convert_duration.hpp>
#include <sge/dinput/joypad/ff/convert_periodic.hpp>
#include <sge/input/joypad/ff/periodic.hpp>
#include <fcppt/cast/size.hpp>


DIPERIODIC
sge::dinput::joypad::ff::convert_periodic(
	sge::input::joypad::ff::periodic const &_periodic
)
{
	return
		DIPERIODIC{
			fcppt::cast::size<
				DWORD
			>(
				_periodic.magnitude().get()
			),
			fcppt::cast::size<
				LONG
			>(
				_periodic.offset().get()
			),
			fcppt::cast::size<
				DWORD
			>(
				_periodic.phase().get()
			),
			sge::dinput::joypad::ff::convert_duration(
				_periodic.period().get()
			)
		};
}
