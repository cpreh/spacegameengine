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


#ifndef SGE_DINPUT_KEYBOARD_HPP_INCLUDED
#define SGE_DINPUT_KEYBOARD_HPP_INCLUDED

#include <map>
#include "../../input/key_type.hpp"
#include "../../string.hpp"
#include "input_device.hpp"
#include "key_converter.hpp"
#include "di.hpp"

namespace sge
{
namespace dinput
{

class keyboard : public input_device {
public:
	keyboard(dinput_ptr, const string& name, GUID guid, sge::win32_window_ptr window, const key_converter& conv);
	void dispatch(input_system::signal_type&);
	key_state query_key(const string& name);
private:
	sge::string::value_type keycode_to_char(const key_code key) const;
	static BOOL CALLBACK enum_keyboard_keys(LPCDIDEVICEOBJECTINSTANCE ddoi, LPVOID ref);

	mod_state modifiers;
	const key_converter& conv;
	HKL kblayout;
	typedef std::map<unsigned,key_type> key_map;
	key_map keys;
};

}
}

#endif
