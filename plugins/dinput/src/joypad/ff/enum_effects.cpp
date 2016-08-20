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
#include <sge/dinput/joypad/ff/enum_effects.hpp>
#include <sge/dinput/joypad/ff/guid_to_type.hpp>
#include <sge/input/exception.hpp>
#include <sge/input/joypad/ff/type_field.hpp>
#include <fcppt/text.hpp>
#include <fcppt/cast/from_void_ptr.hpp>
#include <fcppt/container/bitfield/operators.hpp>
#include <fcppt/optional/maybe_void.hpp>


namespace
{

BOOL
callback(
         LPCDIEFFECTINFO,
         LPVOID
);

}

sge::input::joypad::ff::type_field
sge::dinput::joypad::ff::enum_effects(
	IDirectInputDevice8 &_device
)
{
	sge::input::joypad::ff::type_field data(
		sge::input::joypad::ff::type_field::null()
	);

	if(
		_device.EnumEffects(
			callback,
			&data,
			DIEFT_ALL
		)
		!=
		DI_OK
	)
		throw
			sge::input::exception{
				FCPPT_TEXT("EnumEffects failed")
			};

	return
		data;
}


namespace
{

BOOL
callback(
         LPCDIEFFECTINFO const _info,
         LPVOID const _data
)
{
	sge::input::joypad::ff::type_field &data(
		*fcppt::cast::from_void_ptr<
			sge::input::joypad::ff::type_field *
		>(
			_data
		)
	);

	fcppt::optional::maybe_void(
		sge::dinput::joypad::ff::guid_to_type(
			_info->guid
		),
		[
			&data
		](
			sge::input::joypad::ff::type const _type
		)
		{
			data |=
				_type;
		}
	);

	return
		DIENUM_CONTINUE;
}

}
