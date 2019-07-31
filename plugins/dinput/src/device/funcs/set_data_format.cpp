//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/dinput/di.hpp>
#include <sge/dinput/device/funcs/set_data_format.hpp>
#include <sge/input/exception.hpp>
#include <fcppt/text.hpp>


void
sge::dinput::device::funcs::set_data_format(
	IDirectInputDevice8 &_device,
	DIDATAFORMAT const &_format
)
{
	if(
		_device.SetDataFormat(
			&_format
		)
		!= DI_OK
	)
		throw sge::input::exception(
			FCPPT_TEXT("SetDataFormat() failed!")
		);
}
