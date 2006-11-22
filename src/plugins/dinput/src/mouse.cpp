/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006  Carl Philipp Reh (sefi@s-e-f-i.de)

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/


#include <sstream>
#include "../mouse.hpp"

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

	inline bool is_di_mouse_axis(const DWORD di_mouse)
	{
		return di_mouse == DIMOFS_X || di_mouse == DIMOFS_Y || di_mouse == DIMOFS_Z;
	}
}

sge::dinput::mouse::mouse(const dinput_ptr di, const std::string& name, const GUID guid, const unsigned index, const win32_window_ptr wnd)
: input_device(di,name,guid,index,wnd)
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
			key_state m = reinterpret_cast<long&>(data[i].dwData) / 150.f;
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
		std::ostringstream ss;
		ss << ddoi->tszName << " neg";
		m.l_keys[ddoi->dwOfs] = key_type(ss.str(),m.get_name(),m.get_index(),create_axis_neg_mouse_code(ddoi->dwOfs));
		ss.str("");
		ss << ddoi->tszName << " pos";
		m.r_keys[ddoi->dwOfs] = key_type(ss.str(),m.get_name(),m.get_index(),create_axis_pos_mouse_code(ddoi->dwOfs));
	}
	m.keys[ddoi->dwOfs] = key_type(ddoi->tszName,m.get_name(),m.get_index(),create_mouse_code(ddoi->dwOfs));
	return DIENUM_CONTINUE;
}

namespace
{
	sge::key_code create_axis_neg_mouse_code(const DWORD ofs)
	{
		using namespace sge;
		if(ofs == DIMOFS_X)
			return KC_MOUSEXNEG;
		else if(ofs == DIMOFS_Y)
			return KC_MOUSEYNEG;
		else if(ofs == DIMOFS_Z)
			return KC_MOUSEZNEG;
		return KC_DEFAULT;
	}
	sge::key_code create_axis_pos_mouse_code(const DWORD ofs)
	{
		using namespace sge;
		if(ofs == DIMOFS_X)
			return KC_MOUSEXPOS;
		else if(ofs == DIMOFS_Y)
			return KC_MOUSEYPOS;
		else if(ofs == DIMOFS_Z)
			return KC_MOUSEZPOS;
		return KC_DEFAULT;
	}
	sge::key_code create_mouse_code(const DWORD ofs)
	{
		using namespace sge;
		if(ofs == DIMOFS_BUTTON0)
			return KC_MOUSEL;
		else if(ofs == DIMOFS_BUTTON1)
			return KC_MOUSER;
		else if(ofs == DIMOFS_X)
			return KC_MOUSEX;
		else if(ofs == DIMOFS_Y)
			return KC_MOUSEY;
		else if(ofs == DIMOFS_Z)
			return KC_MOUSEZ;
		return KC_DEFAULT;
	}
}
