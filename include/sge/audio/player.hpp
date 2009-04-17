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


#ifndef SGE_AUDIO_PLAYER_HPP_INCLUDED
#define SGE_AUDIO_PLAYER_HPP_INCLUDED

#include <sge/audio/file_fwd.hpp>
#include <sge/audio/unit.hpp>
#include <sge/audio/sound_fwd.hpp>
#include <sge/audio/pool_fwd.hpp>
#include <sge/export.hpp>
#include <sge/noncopyable.hpp>

namespace sge
{
namespace audio
{

class listener;

class SGE_CLASS_SYMBOL player {
public:
	SGE_NONCOPYABLE(player)
protected:
	SGE_SYMBOL player();
public:
	virtual audio::listener &listener() = 0;
	virtual unit speed_of_sound() const = 0;
	virtual void speed_of_sound(unit) = 0;
	virtual sound_ptr const create_nonstream_sound(file_ptr) = 0;
	virtual sound_ptr const create_stream_sound(file_ptr) = 0;
	SGE_SYMBOL virtual ~player();
};

}
}

#endif // PLAYER_HPP
