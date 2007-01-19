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


#include <iostream>
#include "../keyboard.hpp"

sge::dinput::keyboard::keyboard(const dinput_ptr di, const std::string& name, const GUID guid, const HWND wnd, const key_converter& conv)
: input_device(di,name,guid,wnd), conv(conv)
{
	set_data_format(&c_dfDIKeyboard);
	enum_objects(enum_keyboard_keys);
	acquire();
}

void sge::dinput::keyboard::dispatch(input_system::signal_type& sig)
{
	input_buffer data;
	DWORD elements;
	if(!_get_input(data,elements))
		return;
	for(unsigned i = 0; i < elements; ++i)
	{
		const key_map::const_iterator it = keys.find(data[i].dwOfs);
		if(it == keys.end())
		{
			std::cerr << "Missing key in keyboard. Not dispatching.\n";
			continue;
		}
		sig(key_pair(it->second, data[i].dwData & 0x80 ? 1.f : 0));
	}
}

BOOL sge::dinput::keyboard::enum_keyboard_keys(LPCDIDEVICEOBJECTINSTANCE ddoi,  LPVOID s)
{
	keyboard& k = *static_cast<keyboard*>(s);
	const std::string key_name(ddoi->tszName);
	k.keys[ddoi->dwOfs] = key_type(k.name() + '_' + ddoi->tszName, k.conv.create_key_code(ddoi->dwOfs), key_name.size() == 1 ? key_name[0] : 0);
	return DIENUM_CONTINUE;
}
