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

#include <sge/config.h>
#include "player.hpp"
#ifdef SGE_WINDOWS_PLATFORM
#include <al.h>
#else
#include <AL/al.h>
#endif
#include <sge/string.hpp>
#include <sge/audio/player/sound.hpp>

namespace sge
{
namespace openal
{

class nonstream_sound : public audio::sound
{
	player &      player_;
	mutable sound_status  status_;
	bool          loop_,positional_;
	math::vector3 pos_;

	ALuint al_buffer_;
	mutable ALuint al_source_;

	void check(const string &);
	void sync() const;
public:
	nonstream_sound(audio::file_ptr, player &);
	~nonstream_sound();
	void play(const bool);
	void toggle_pause();
	sound_status status() const;
	void stop();
	bool positional() const { return positional_; }
	void positional(const bool);
	math::vector3 pos() const { return pos_; }
	void pos(const math::vector3 &);
};
}
}

#endif
