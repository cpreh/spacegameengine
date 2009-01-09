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


#include "../keyboard.hpp"
#include <sge/input/key_pair.hpp>
#include <sge/iostream.hpp>
#include <boost/tr1/array.hpp>
#include <ostream>

sge::dinput::keyboard::keyboard(
	dinput_ptr const di,
	string const &name,
	GUID const guid,
	windows::window_ptr const window,
	key_converter const &conv)
:
	device(
		di,
		name,
		guid,
		window),
	modifiers(false, false, false),
	conv(conv),
	kblayout(GetKeyboardLayout(0))
{
	set_data_format(&c_dfDIKeyboard);
	enum_objects(enum_keyboard_keys);
	acquire();
}

void sge::dinput::keyboard::dispatch(signal_type &sig)
{
	input_buffer data;
	DWORD elements;
	if(!get_input(data,elements))
		return;
	for(unsigned i = 0; i < elements; ++i)
	{
		input::key_type key = keys[data[i].dwOfs];

		const bool key_value = static_cast<bool>(data[i].dwData & 0x80);
		switch(data[i].dwOfs) {
		case VK_CONTROL:
			modifiers.ctrl = key_value;
			break;
		case VK_MENU:
			modifiers.alt = key_value;
			break;
		case VK_SHIFT:
			modifiers.shift = key_value;
			break;
		}

		key.char_code(keycode_to_char(key.code()));
		sig(input::key_pair(key, key_value ? static_cast<input::key_state>(1) : 0));
	}
}

BOOL sge::dinput::keyboard::enum_keyboard_keys(LPCDIDEVICEOBJECTINSTANCE ddoi,  LPVOID s)
{
	keyboard &k = *static_cast<keyboard*>(s);
	input::key_type::string const key_name(
		ddoi->tszName);

	k.keys[ddoi->dwOfs] = input::key_type(
		k.name() + key_name,
		k.conv.create_key_code(
			ddoi->dwOfs),
		key_name.size() == 1
			? key_name[0]
			: 0);
	return DIENUM_CONTINUE;
}

sge::char_type
sge::dinput::keyboard::keycode_to_char(
	input::key_code const key) const
{
	std::tr1::array<BYTE,256> state;
	const BYTE key_up = 0, key_down = 0x80;
	state[VK_SHIFT]   = modifiers.shift ? key_down : key_up;
	state[VK_MENU]    = modifiers.alt   ? key_down : key_up;
	state[VK_CONTROL] = modifiers.ctrl  ? key_down : key_up;

	const unsigned dik = conv.create_dik(key);
	const unsigned vk = MapVirtualKeyEx(dik, 1, kblayout);

	WORD result;
	if(ToAsciiEx(vk, dik, state.c_array(), &result, 0, kblayout) == 1)
		return *reinterpret_cast<char*>(&result);
	sge::cerr << SGE_TEXT("stub: Key names with more than one char are not supported.\n");
	return 0;
}
