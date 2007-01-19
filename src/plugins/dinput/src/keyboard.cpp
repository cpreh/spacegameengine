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
#include <boost/array.hpp>
#include "../keyboard.hpp"

sge::dinput::keyboard::keyboard(const dinput_ptr di, const std::string& name, const GUID guid, const HWND wnd, const key_converter& conv)
: input_device(di,name,guid,wnd),
  conv(conv),
  kblayout(GetKeyboardLayout(0))
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
		key_type key = keys[data[i].dwOfs];
		key.char_code = keycode_to_char(key.code);
		sig(key_pair(key, data[i].dwData & 0x80 ? 1.f : 0));
	}
}

BOOL sge::dinput::keyboard::enum_keyboard_keys(LPCDIDEVICEOBJECTINSTANCE ddoi,  LPVOID s)
{
	keyboard& k = *static_cast<keyboard*>(s);
	const std::string key_name(ddoi->tszName);
	k.keys[ddoi->dwOfs] = key_type(k.name() + '_' + ddoi->tszName, k.conv.create_key_code(ddoi->dwOfs), key_name.size() == 1 ? key_name[0] : 0);
	return DIENUM_CONTINUE;
}

sge::uchar_t sge::dinput::keyboard::keycode_to_char(const key_code key) const
{
	boost::array<BYTE,256> state;
	const BYTE key_up = 0, key_down = 0x80;
//	state[VK_SHIFT] = mod_state.shift_down ? key_down : key_up;
//	state[VK_MENU] = mod_state.alt_down ? key_down : key_up;
//	state[VK_CONTROL] = mod_state.ctrl_down ? key_down : key_up;

	const unsigned dik = conv.create_dik(key);
	const unsigned vk = MapVirtualKeyEx(dik, 1, kblayout);

	WORD result;
	if(ToAsciiEx(vk, dik, state.c_array(), &result, 0, kblayout) == 1)
		return *reinterpret_cast<char*>(&result);
	std::cerr << "stub: Keys names with more than one char are not supported.\n";
	return 0;
}

