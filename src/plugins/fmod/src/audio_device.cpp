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
#include "../audio_device.hpp"
#include "../music.hpp"
#include "../../../core/main/ptr_cast.hpp"

#ifdef SGE_WINDOWS_PLATFORM
#include "../../../core/main/win32_window.hpp"
#endif

sge::fmod::audio_device::audio_device(const unsigned num, const window_ptr w)
{
	if(w)
	{
#ifdef SGE_WINDOWS_PLATFORM
		win32_window* ww = ptr_cast<win32_window*>(w.get());
		if(FSOUND_SetHWND(ww->ge_hwnd()) == false)
			throw std::runtime_error("FSOUND_SetHWND() failed");
#endif
	}
	if(FSOUND_SetDriver(num) == false)
		throw std::runtime_error("Unable to set sound driver");
	if(FSOUND_Init(44100, 32, 0) == false)
		throw std::runtime_error("Unable to init fmod");
}

sge::fmod::audio_device::~audio_device()
{
	FSOUND_Close();
}

sge::music_ptr sge::fmod::audio_device::load_music(const std::string& file)
{
	return music_ptr(new music(file));
}
