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
#include <sge/dinput/joypad/ff/create_effect.hpp>
#include <sge/dinput/joypad/ff/dinput_effect_unique_ptr.hpp>
#include <sge/input/exception.hpp>
#include <fcppt/text.hpp>


sge::dinput::joypad::ff::dinput_effect_unique_ptr
sge::dinput::joypad::ff::create_effect(
	IDirectInputDevice8 &_device,
	REFGUID _guid,
	DIEFFECT const &_effect
)
{
	IDirectInputEffect *result;

	if(
		_device.CreateEffect(
			_guid,
			&_effect,
			&result,
			nullptr
		)
		!=
		DI_OK
	)
		throw
			sge::input::exception{
				FCPPT_TEXT("CreateEffect failed")
			};

	return
		sge::dinput::joypad::ff::dinput_effect_unique_ptr{
			result
		};
}
