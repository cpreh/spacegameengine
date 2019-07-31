//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/dinput/di.hpp>
#include <sge/dinput/device/get_property.hpp>
#include <sge/dinput/device/get_property_dword.hpp>
#include <fcppt/cast/size.hpp>


DWORD
sge::dinput::device::get_property_dword(
	IDirectInputDevice8 &_device,
	DIDEVICEOBJECTINSTANCE const &_data,
	REFGUID _guid
)
{
	DIPROPDWORD result;

	result.diph.dwSize =
		fcppt::cast::size<
			DWORD
		>(
			sizeof(DIPROPDWORD)
		);

	sge::dinput::device::get_property(
		_device,
		_data,
		_guid,
		result.diph
	);

	return
		result.dwData;
}
