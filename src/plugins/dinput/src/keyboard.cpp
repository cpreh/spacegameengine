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


#include <vector>
#include "../keyboard.hpp"

sge::dinput::keyboard::keyboard(const dinput_ptr di, const std::string& name, const GUID guid, const unsigned index, const win32_window_ptr wnd, const key_converter& conv)
: input_device(di,name,guid,index,wnd), conv(conv)
{
	set_data_format(&c_dfDIKeyboard);
	enum_objects(enum_keyboard_keys);
	acquire();
}

void sge::dinput::keyboard::get_input(input_array& v)
{
	input_buffer data;
	DWORD elements;
	if(!_get_input(data,elements))
		return;
	for(unsigned i = 0; i < elements; ++i)
		v.push_back(key_pair(keys[data[i].dwOfs],data[i].dwData & 0x80 ? 1.f : 0));
}

BOOL sge::dinput::keyboard::enum_keyboard_keys(LPCDIDEVICEOBJECTINSTANCE ddoi,  LPVOID s)
{
	keyboard& k = *static_cast<keyboard*>(s);
	k.keys[ddoi->dwOfs] = key_type(ddoi->tszName,k.get_name(),k.get_index(),k.conv.create_key_code(ddoi->dwOfs));
	return DIENUM_CONTINUE;
}
