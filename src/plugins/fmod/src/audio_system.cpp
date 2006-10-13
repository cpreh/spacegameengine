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


#include <stdexcept>
#include "../audio_system.hpp"
#include "../audio_device.hpp"
#include <fmod.h>

sge::fmod::audio_system::audio_system(const window_ptr w)
: w(w)
{
	if(FSOUND_SetOutput(-1) == false)
		throw std::runtime_error("FSOUND_SetOutput() failed");
}

sge::audio_device_ptr sge::fmod::audio_system::create_audio_device(const unsigned num)
{
	return audio_device_ptr(new audio_device(num,w));
}

void sge::fmod::audio_system::get_driver_info(driver_info_array& v)
{
	const int num = FSOUND_GetNumDrivers();
	v.reserve(num);
	for(int i = 0; i < num; ++i)
	{
		driver_info di;
		di.name = FSOUND_GetDriverName(i);
		v.push_back(di);
	}
}
