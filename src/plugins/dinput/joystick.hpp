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


#ifndef SGE_DINPUT_JOYSTICK_HPP_INCLUDED
#define SGE_DINPUT_JOYSTICK_HPP_INCLUDED

#include "input_device.hpp"
#include "di.hpp"
#include <map>

namespace sge
{
namespace dinput
{

class joystick : public input_device {
public:
	joystick(dinput_ptr di, GUID guid, unsigned index, windows::window_ptr window);
	void dispatch(signal_type &);
private:
	static BOOL CALLBACK enum_joystick_keys(LPCDIDEVICEOBJECTINSTANCE ddoi, LPVOID ref);
	typedef std::map<unsigned, input::key_type> key_map;
	key_map  keys;
	key_map  l_keys;
	key_map  r_keys;
};

}
}

#endif
