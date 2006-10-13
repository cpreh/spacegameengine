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


#ifndef SGE_FMOD_AUDIO_SYSTEM_HPP_INCLUDED
#define SGE_FMOD_AUDIO_SYSTEM_HPP_INCLUDED

#include "../../core/audio/audio_system.hpp"

namespace sge
{
	namespace fmod
	{
		class audio_system : public sge::audio_system {
		public:
			audio_system(window_ptr w);
			void get_driver_info(driver_info_array& v);
			audio_device_ptr create_audio_device(unsigned num);
		private:
			window_ptr w;
		};
	}
}

#endif
