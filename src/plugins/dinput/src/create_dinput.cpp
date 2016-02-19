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


#include <sge/dinput/create_dinput.hpp>
#include <sge/dinput/di.hpp>
#include <sge/dinput/dinput_unique_ptr.hpp>
#include <sge/input/exception.hpp>
#include <awl/backends/windows/module_handle.hpp>
#include <fcppt/text.hpp>
#include <fcppt/cast/from_void_ptr.hpp>


sge::dinput::dinput_unique_ptr
sge::dinput::create_dinput()
{
	LPVOID ret(
		nullptr
	);

	if(
		::DirectInput8Create(
			awl::backends::windows::module_handle(),
			DIRECTINPUT_VERSION,
			IID_IDirectInput8,
			&ret,
			nullptr
		)
		!= DI_OK
	)
		throw sge::input::exception(
			FCPPT_TEXT("Cannot create DirectInput!")
		);

	return
		sge::dinput::dinput_unique_ptr(
			fcppt::cast::from_void_ptr<
				IDirectInput8 *
			>(
				ret
			)
		);
}
