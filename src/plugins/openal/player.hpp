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


#ifndef SGE_OPENAL_PLAYER_INCLUDED
#define SGE_OPENAL_PLAYER_INCLUDED

#include "device.hpp"
#include "context.hpp"
#include "openal.hpp"
#include "buffer.hpp"
#include "listener.hpp"

#include <sge/audio/player.hpp>
#include <sge/audio/sound.hpp>
#include <sge/audio/types.hpp>

#include <boost/ptr_container/ptr_list.hpp>

namespace sge
{
namespace openal
{
class stream_sound;

class player : public audio::player
{
public:
	player();
	void update();

	void register_stream_sound(stream_sound *p);
	void unregister_stream_sound(stream_sound *p);

	ALuint register_nonstream_sound(audio::file_ptr);
	void unregister_nonstream_sound(ALuint);

	audio::listener &listener() { return listener_; }
		
	audio::sound_ptr const create_nonstream_sound(audio::file_ptr);
	audio::sound_ptr const create_stream_sound(audio::file_ptr);
private:
	typedef boost::ptr_list<stream_sound,boost::view_clone_allocator> 
		stream_sound_container;
	typedef boost::ptr_list<buffer> 
		nonstream_sound_container;

	stream_sound_container    stream_sounds;
	nonstream_sound_container nonstream_sounds;
	device                    device_;
	context                   context_;
	sge::openal::listener     listener_;
};

}
}

#endif 
