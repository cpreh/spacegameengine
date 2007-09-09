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


#ifndef SGE_DINPUT_INPUT_SYSTEM_HPP_INCLUDED
#define SGE_DINPUT_INPUT_SYSTEM_HPP_INCLUDED

#include <map>
#include <boost/ptr_container/ptr_vector.hpp>
#include "../../input/input_system.hpp"
#include "../../win32_window.hpp"
#include "key_converter.hpp"
#include "input_device.hpp"
#include "di.hpp"

namespace sge
{
namespace dinput
{

class input_system : public sge::input_system {
public:
	input_system(win32_window_ptr w);
	boost::signals::connection register_callback(const callback& c);
	boost::signals::connection register_repeat_callback(const repeat_callback& c);
	void dispatch();
	sge::window_ptr get_window() const;

private:
	signal_type sig;
	repeat_signal_type repeat_sig;

	typedef dinput_device_ptr key_map;
	typedef std::map<std::string,key_map> key_mapper_u;
	typedef std::multimap<std::string,key_map> key_mapper_m;
	typedef std::pair<std::string,key_map> key_map_pair;
	typedef boost::ptr_vector<input_device> device_array;
	typedef std::map<key_code,bool> key_code_press_map;
	key_mapper_u       map_u;
	key_mapper_m       map_m;
	key_code_press_map key_codes_pressed;
	device_array       devices;
	dinput_ptr         di;
	win32_window_ptr   wnd;
	key_converter      key_conv;

	static BOOL CALLBACK di_enum_devices_callback(LPCDIDEVICEINSTANCE ddi, LPVOID s);
};

}
}

#endif
