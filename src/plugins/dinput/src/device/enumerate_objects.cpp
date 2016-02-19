/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2016 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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
#include <sge/dinput/device/enumerate_objects.hpp>
#include <sge/dinput/device/enumerator.hpp>
#include <sge/input/exception.hpp>
#include <fcppt/text.hpp>


namespace
{

BOOL
CALLBACK
dispatcher(
	LPCDIDEVICEOBJECTINSTANCE,
	LPVOID
);

}

void
sge::dinput::device::enumerate_objects(
	IDirectInputDevice8 &_device,
	sge::dinput::device::enumerator &_enumerator,
	DWORD const _flags
)
{
	if(
		_device.EnumObjects(
			&dispatcher,
			static_cast<
				void *
			>(
				&_enumerator
			),
			_flags
		)
		!= DI_OK
	)
		throw sge::input::exception(
			FCPPT_TEXT("enumerating objects failed!")
		);
}

namespace
{

BOOL
CALLBACK
dispatcher(
	LPCDIDEVICEOBJECTINSTANCE const _object,
	LPVOID const _ptr
)
{
	static_cast<
		sge::dinput::device::enumerator *
	>(
		_ptr
	)->dispatch(
		*_object
	);

	return DIENUM_CONTINUE;
}

}
