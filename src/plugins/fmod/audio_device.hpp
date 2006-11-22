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


#ifndef SGE_FMOD_AUDIO_DEVICE_HPP_INCLUDED
#define SGE_FMOD_AUDIO_DEVICE_HPP_INCLUDED

#include "../../audio/audio_device.hpp"
#include "../../window.hpp"

namespace sge
{
namespace fmod
{

class audio_device : public sge::audio_device {
public:
	audio_device(unsigned num, window_ptr w);
	~audio_device();
	music_ptr load_music(const std::string& file);
};

}
}

#endif
