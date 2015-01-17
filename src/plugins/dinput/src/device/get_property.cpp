/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2015 Carl Philipp Reh (carlphilippreh <at> gmail.com)

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/


#include <sge/dinput/di.hpp>
#include <sge/dinput/device/get_property.hpp>
#include <sge/input/exception.hpp>
#include <fcppt/text.hpp>
#include <fcppt/cast/size.hpp>


void
sge::dinput::device::get_property(
	IDirectInputDevice8 &_device,
	DIDEVICEOBJECTINSTANCE const &_data,
	REFGUID _guid,
	DIPROPHEADER &_result
)
{
	_result.dwHeaderSize =
		fcppt::cast::size<
			DWORD
		>(
			sizeof(DIPROPHEADER)
		);

	_result.dwHow = DIPH_BYOFFSET;

	_result.dwObj = _data.dwOfs;

	switch(
		_device.GetProperty(
			_guid,
			&_result
		)
	)
	{
	case DI_OK:
	case S_FALSE:
		break;
	default:
		throw sge::input::exception(
			FCPPT_TEXT("GetProperty failed!")
		);
	}
}
