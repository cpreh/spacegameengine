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


#include "../create_dinput.hpp"
#include "../di.hpp"
#include "../dinput_unique_ptr.hpp"
#include <sge/input/exception.hpp>
#include <awl/backends/windows/module_handle.hpp>
#include <fcppt/text.hpp>


sge::dinput::dinput_unique_ptr
sge::dinput::create_dinput()
{
	IDirectInput8 *instance;

	if(
		::DirectInput8Create(
			awl::backends::windows::module_handle(),
			DIRECTINPUT_VERSION,
			IID_IDirectInput8A,
			reinterpret_cast<LPVOID *>(&instance), // this is undefined but Direct Input wants us to do it
			0
		)
		!= DI_OK
	)
		throw sge::input::exception(
			FCPPT_TEXT("Cannot create direct input!")
		);

	return
		dinput::dinput_unique_ptr(
			instance
		);
}
