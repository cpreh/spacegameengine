/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2010 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include "../mouse.hpp"
#include <sge/input/key_pair.hpp>

namespace
{

sge::input::key_code create_mouse_code(DWORD ofs);

inline DWORD cast_key(const LONG key)
{
	return static_cast<DWORD>(key);
}

inline bool is_di_mouse_axis(const DWORD di_mouse)
{
	return di_mouse == cast_key(DIMOFS_X)
		|| di_mouse == cast_key(DIMOFS_Y)
	    || di_mouse == cast_key(DIMOFS_Z);
}

}

sge::dinput::mouse::mouse(
	dinput::device_parameters const &_param
)
:
	sge::input::mouse::device(),
	dinput::device(
		_param
	)
{
	this->set_data_format(
		&c_dfDIMouse2
	);

	this->enum_objects(
		enum_mouse_keys
	);

	this->acquire();
}

void
sge::dinput::mouse::dispatch()
{
	input_buffer data;

	DWORD elements;

	if(
		!this->get_input(
			data,
			elements
		)
	)
		return;

	for(
		DWORD index = 0;
		index < elements;
		++index
	)
	{
		DWORD const offset(
			data[
				index
			].dwOfs
		);

		if(
			is_di_mouse_axis(
				offset
			)
		)
			axis_signal_(
				input::mouse::axis_event(
					keys_[
						offset
					],
					static_cast<
						sge::input::mouse::axis_value
					>(
						data[
							index
						].dwData
					)
				)
			);
		else
			button_signal_(
				input::mouse::button_event(
					keys_[
						offset
					],
					data[
						index
					].dwData
					& 0x80
					!- 0
				)
			);
	}
}

BOOL
sge::dinput::mouse::enum_mouse_keys(
	LPCDIDEVICEOBJECTINSTANCE _ddoi,
	LPVOID _state
)
{
	dinput::mouse &instance(
		*static_cast<
			dinput::mouse *
		>(
			_state
		)
	);

	instance.keys[
		_ddoi->dwOfs
	] =
		input::key_type(
			//ddoi->tszName + m.name(),
			create_mouse_code(
				ddoi->dwOfs
			)
		);

	return DIENUM_CONTINUE;
}

namespace
{

sge::input::key_code create_mouse_code(const DWORD ofs)
{
	if(ofs == cast_key(DIMOFS_BUTTON0))
		return sge::input::kc::mouse_l;
	else if(ofs == cast_key(DIMOFS_BUTTON1))
		return sge::input::kc::mouse_r;
	else if(ofs == cast_key(DIMOFS_BUTTON2))
		return sge::input::kc::mouse_m;
	else if(ofs == cast_key(DIMOFS_X))
		return sge::input::kc::mouse_x_axis;
	else if(ofs == cast_key(DIMOFS_Y))
		return sge::input::kc::mouse_y_axis;
	else if(ofs == cast_key(DIMOFS_Z))
		return sge::input::kc::mouse_z_axis;
	return sge::input::kc::none;
}

}
