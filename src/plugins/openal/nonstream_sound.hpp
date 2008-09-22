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


#ifndef SGE_OPENAL_NONSTREAM_SOUND_INCLUDED
#define SGE_OPENAL_NONSTREAM_SOUND_INCLUDED

#include <sge/audio/file.hpp>
#include "source.hpp"

namespace sge
{
namespace openal
{
class player;

class nonstream_sound : public source
{
public:
	nonstream_sound(audio::file_ptr,player&);
	void play_mode(audio::play_mode::type);
	~nonstream_sound();
private:
	player &player_;
	ALuint al_buffer_;
};
}
}

#endif
