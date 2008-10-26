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


#ifndef SGE_OPENAL_STREAM_SOUND_INCLUDED
#define SGE_OPENAL_STREAM_SOUND_INCLUDED

#include "player.hpp"
#include "source.hpp"
#include <sge/audio/sound.hpp>
#include <sge/audio/file.hpp>
#include <sge/math/vector.hpp>
#include <sge/shared_ptr.hpp>
#include <sge/string.hpp>

namespace sge
{
namespace openal
{
class stream_sound : public source
{
	public:
	stream_sound(audio::file_ptr,player&);
	void update();
	void do_play();
	private:
	player &                       player_;
	audio::file_ptr const          audio_file_;
	audio::sample_count const      buffer_samples_;
	ALenum const                   format_;
	ALuint                         al_buffers_[2];

	bool fill_buffer(ALuint);
};
}
}

#endif
