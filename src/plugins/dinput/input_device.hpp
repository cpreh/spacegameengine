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


#ifndef SGE_DINPUT_INPUT_DEVICE_HPP_INCLUDED
#define SGE_DINPUT_INPUT_DEVICE_HPP_INCLUDED

#include <cstddef>
#include "../../input/input_system.hpp"
#include "../../input/key_type.hpp"
#include "di.hpp"

namespace sge
{
namespace dinput
{

class input_device {
public:
	virtual void dispatch(input_system::signal_type&) = 0;
	virtual ~input_device(){}
protected:
	input_device(dinput_ptr di, const string& name, GUID Guid, HWND wnd);
	void acquire();
	void poll();
	void set_data_format(LPCDIDATAFORMAT lpdf);
	void set_property(REFGUID rguidProp, LPCDIPROPHEADER pdiph);

	static const std::size_t buffer_size = 1024;
	typedef DIDEVICEOBJECTDATA input_buffer[buffer_size];

	bool _get_input(input_buffer buf, DWORD& elements);
	void enum_objects(LPDIENUMDEVICEOBJECTSCALLBACK fun);
	const string& name() const;
private:
	void set_cooperative_level(HWND hwnd, DWORD flags);
	static const DIPROPDWORD  buffer_settings;
	static const DWORD        coop_level;
	dinput_device_ptr         device;
	string                    _name;
};

typedef shared_ptr<input_device> input_device_ptr;
 
}
}

#endif
