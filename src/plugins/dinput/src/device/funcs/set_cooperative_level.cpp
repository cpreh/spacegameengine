/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2011 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include <sge/dinput/device/funcs/set_cooperative_level.hpp>
#include <sge/input/exception.hpp>
#include <awl/backends/windows/window/instance.hpp>
#include <fcppt/text.hpp>


void
sge::dinput::device::funcs::set_cooperative_level(
	IDirectInputDevice8 *const _device,
	awl::backends::windows::window::instance &_window,
	DWORD const _flags
)
{
	if(
		_device->SetCooperativeLevel(
			_window.hwnd(),
			_flags
		)
		!= DI_OK
	)
		throw sge::input::exception(
			FCPPT_TEXT("SetCooperativeLevel() failed!")
		);
}
