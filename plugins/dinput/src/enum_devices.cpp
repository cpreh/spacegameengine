//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/dinput/di.hpp>
#include <sge/dinput/enum_devices.hpp>
#include <sge/dinput/enum_devices_function.hpp>
#include <sge/input/exception.hpp>
#include <fcppt/text.hpp>


void
sge::dinput::enum_devices(
	IDirectInput8 &_dinput,
	sge::dinput::enum_devices_function const _function,
	void *const _data
)
{
	if(
		_dinput.EnumDevices(
			DI8DEVCLASS_ALL,
			_function,
			_data,
			DIEDFL_ATTACHEDONLY
		)
		!= DI_OK
	)
		throw
			sge::input::exception{
				FCPPT_TEXT("DirectInput Enumeration failed!")
			};
}
