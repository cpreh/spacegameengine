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
#include "source_wrapper.hpp"
#include <sge/audio/player/sound.hpp>
#include <sge/shared_ptr.hpp>
#include <sge/string.hpp>
#include <sge/math/vector.hpp>

namespace sge
{
namespace openal
{
class stream_sound : public audio::sound
{
	public:
	stream_sound(audio::file_ptr,player&);
	void play(play_mode::type);
	void toggle_pause();
	sound_status::type status() const;
	void stop();
	void update();
	bool positional() const { return positional_; }
	void positional(bool);
	math::vector3 const pos() const { return pos_; }
	void pos(const math::vector3 &);
	~stream_sound();
	private:
	player &                    player_;
	audio::file_ptr const       audio_file_;
	audio::sample_type const    buffer_samples_;
	ALenum const                format_;
	math::vector3               pos_;
	play_mode::type             play_mode_;
	bool                        positional_;
	ALuint                      al_buffers_[2];
	mutable sound_status::type  status_;
	mutable source_wrapper      source_;

	bool fill_buffer(ALuint);
};
}
}

#endif
