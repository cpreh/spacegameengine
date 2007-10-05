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

#include <cstddef>
#include "../../audio/audio_player/sound.hpp"
#include "../../shared_ptr.hpp"
#include "../../math/vector.hpp"
#include "openal_player.hpp"

namespace sge
{
namespace openal
{
class stream_sound : public sound
{
	player &                    player_;
	shared_ptr<sge::audio_file> audio_file_;
	std::size_t                 buffer_samples_;
	math::vector3               pos_;
	bool                        loop_,positional_;
	mutable sound_status        status_;

	// OpenAL-Zeugs
	ALenum format_;
	ALuint al_buffers_[2];
	mutable ALuint al_source_;

	bool fill_buffer(ALuint);
	void check(const std::string &);
	void sync() const;
	public:
	stream_sound(shared_ptr<audio_file>,player &);
	~stream_sound();
	void play(const bool);
	void toggle_pause();
	sound_status status() const;
	void stop();
	void update();
	bool positional() const { return positional_; }
	void positional(const bool);
	math::vector3 pos() const { return pos_; }
	void pos(const math::vector3 &);
};
}
}

#endif
