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



#ifndef SGE_DINPUT_KEYBOARD_HPP_INCLUDED
#define SGE_DINPUT_KEYBOARD_HPP_INCLUDED

#include "device.hpp"
#include "key_converter.hpp"
#include "di.hpp"
#include <sge/input/key_type.hpp>
#include <sge/input/key_state.hpp>
#include <sge/input/mod_state.hpp>
#include <sge/string.hpp>
#include <sge/char.hpp>
#include <map>

namespace sge
{
namespace dinput
{

class keyboard : public device {
public:
	keyboard(
		dinput_ptr,
		string const &name,
		GUID guid,
		windows::window_ptr window,
		key_converter const &conv);
	void dispatch(signal_type &);
	input::key_state query_key(string const &name);
private:
	char_type keycode_to_char(
		input::key_code key) const;
	
	static BOOL CALLBACK enum_keyboard_keys(LPCDIDEVICEOBJECTINSTANCE ddoi, LPVOID ref);

	input::mod_state modifiers;
	key_converter const &conv;
	HKL kblayout;
	typedef std::map<
		unsigned,
		input::key_type
	> key_map;
	key_map keys;
};

}
}

#endif
