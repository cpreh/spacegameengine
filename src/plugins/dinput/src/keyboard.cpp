/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2009 Carl Philipp Reh (sefi@s-e-f-i.de)

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
#include "../keyboard_repeat.hpp"
#include <sge/input/key_pair.hpp>
#include <sge/time/resolution.hpp>
#include <sge/log/headers.hpp>
#include <sge/optional_impl.hpp>
#include <sge/text.hpp>
#include <sge/exception.hpp>
#include <boost/tr1/array.hpp>
#include <ostream>

sge::dinput::keyboard::keyboard(
	dinput_ptr const di,
	string const &name,
	GUID const guid,
	windows::window_ptr const window,
	key_converter const &conv,
	repeat_signal_type &repeat_sig)
:
	device(
		di,
		name,
		guid,
		window),
	modifiers(false, false, false),
	conv(conv),
	kblayout(GetKeyboardLayout(0)),
	repeat_sig(repeat_sig),
	repeat_time(
		keyboard_repeat(),
		sge::time::activation_state::active
	),
	old_key(),
	keys()
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

		bool const key_value(
			static_cast<bool>(
				data[i].dwData & 0x80
			)
		);

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

		key.char_code(
			keycode_to_char(
				key.code()
			)
		);

		sig(
			input::key_pair(
				key,
				key_value
				? 1
				: 0
			)
		);

		if(!old_key || *old_key != key)
		{
			repeat_time.expire();
			old_key = key;
		}
		else if(repeat_time.update_b())
			repeat_sig(
				key
			);
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
	BYTE const key_up = 0, key_down = 0x80;
	state[VK_SHIFT]   = modifiers.shift ? key_down : key_up;
	state[VK_MENU]    = modifiers.alt   ? key_down : key_up;
	state[VK_CONTROL] = modifiers.ctrl  ? key_down : key_up;

	unsigned const
		dik = conv.create_dik(key),
		vk = MapVirtualKeyEx(dik, 1, kblayout);

	WORD result;
	switch(
		ToAsciiEx(
			vk,
			dik,
			state.data(),
			&result,
			0,
			kblayout))
	{
	case 0:
		SGE_LOG_WARNING(
			log::global(),
			log::_1
				<< SGE_TEXT("No translation found for dik: ")
				<< dik);
		return 0;
	case 1:
		return static_cast<char_type>(result & 0xFF);
	case 2:
		SGE_LOG_WARNING(
			log::global(),
			log::_1
				<< SGE_TEXT("stub: Key names with more than one char are not supported."));
		return 0;
	default:
		throw exception(
			SGE_TEXT("Invalid return value of ToAsciiEx!"));
	}
}
