/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2007  Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include <sstream>
#include "../mouse.hpp"
#include "../../../win32_conv.hpp"

namespace
{

inline void bound_pos(sge::key_state& state)
{
	if(state > 1.f)
		state = 1.f;
	else if(state < 0)
		state = 0;
}

inline void bound_pos_neg(sge::key_state& state)
{
	if(state > 1.f)
		state = 1.f;
	else if(state < -1.f)
		state = -1.f;
}

sge::key_code create_mouse_code(DWORD ofs);
sge::key_code create_axis_neg_mouse_code(DWORD ofs);
sge::key_code create_axis_pos_mouse_code(DWORD ofs);

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

sge::dinput::mouse::mouse(const dinput_ptr di, const string& name, const GUID guid, sge::win32_window_ptr window)
: input_device(di,name,guid,window)
{
	set_data_format(&c_dfDIMouse2);
	enum_objects(enum_mouse_keys);
	acquire();
}

void sge::dinput::mouse::dispatch(input_system::signal_type& sig)
{
	input_buffer data;
	DWORD elements;
	if(!_get_input(data,elements))
		return;

	for(unsigned i = 0; i < elements; ++i)
	{
		if(is_di_mouse_axis(data[i].dwOfs))
		{
			key_state m = reinterpret_cast<long&>(data[i].dwData);// / 150.f;
			key_state l = -m;
			key_state r = m;
			bound_pos(l);
			bound_pos(r);
			bound_pos_neg(m);

			sig(key_pair(keys[data[i].dwOfs],m));
			sig(key_pair(l_keys[data[i].dwOfs],l));
			sig(key_pair(r_keys[data[i].dwOfs],r));
		}
		else
			sig(key_pair(keys[data[i].dwOfs],data[i].dwData & 0x80 ? 1.f : 0));
	}
}

BOOL sge::dinput::mouse::enum_mouse_keys(LPCDIDEVICEOBJECTINSTANCE ddoi, LPVOID s)
{
	mouse& m = *static_cast<mouse*>(s);
	if(is_di_mouse_axis(ddoi->dwOfs))
	{
		win_ostringstream ss;
		ss << ddoi->tszName << TEXT("_neg");
		m.l_keys[ddoi->dwOfs] = key_type(win_str_to_sge(ss.str()) + m.name(), create_axis_neg_mouse_code(ddoi->dwOfs));
		ss.str(TEXT(""));
		ss << ddoi->tszName << TEXT("_pos");
		m.r_keys[ddoi->dwOfs] = key_type(win_str_to_sge(ss.str()) + m.name(), create_axis_pos_mouse_code(ddoi->dwOfs));
	}
	m.keys[ddoi->dwOfs] = key_type(win_str_to_sge(ddoi->tszName) + m.name(),create_mouse_code(ddoi->dwOfs));
	return DIENUM_CONTINUE;
}

namespace
{

sge::key_code create_axis_neg_mouse_code(const DWORD ofs)
{
	if(ofs == cast_key(DIMOFS_X))
		return sge::kc::mouse_axis_x_neg;
	if(ofs == cast_key(DIMOFS_Y))
		return sge::kc::mouse_axis_y_neg;
	if(ofs == cast_key(DIMOFS_Z))
		return sge::kc::mouse_axis_z_neg;
	return sge::kc::none;
}

sge::key_code create_axis_pos_mouse_code(const DWORD ofs)
{
	if(ofs == cast_key(DIMOFS_X))
		return sge::kc::mouse_axis_x_pos;
	else if(ofs == cast_key(DIMOFS_Y))
		return sge::kc::mouse_axis_y_pos;
	else if(ofs == cast_key(DIMOFS_Z))
		return sge::kc::mouse_axis_z_pos;
	return sge::kc::none;
}

sge::key_code create_mouse_code(const DWORD ofs)
{
	if(ofs == cast_key(DIMOFS_BUTTON0))
		return sge::kc::mouse_l;
	else if(ofs == cast_key(DIMOFS_BUTTON1))
		return sge::kc::mouse_r;
	else if(ofs == cast_key(DIMOFS_X))
		return sge::kc::mouse_axis_x;
	else if(ofs == cast_key(DIMOFS_Y))
		return sge::kc::mouse_axis_y;
	else if(ofs == cast_key(DIMOFS_Z))
		return sge::kc::mouse_axis_z;
	return sge::kc::none;
}
}
