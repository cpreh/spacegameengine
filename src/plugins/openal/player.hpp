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

#include <sge/config.h>
#ifdef SGE_WINDOWS_PLATFORM
#include <al.h>
#include <alc.h>
#else
#include <AL/al.h>
#include <AL/alc.h>
#endif
#include <sge/shared_ptr.hpp>
#include <sge/string.hpp>
#include <sge/audio/player/player.hpp>
#include <sge/audio/player/sound_angle.hpp>
#include <sge/audio/player/sound.hpp>
#include <memory>
#include <list>
#include <vector>

namespace sge
{
namespace openal
{

class stream_sound;

class player : public audio::player
{
	// TODO: create own files for these classes
	struct buffer_map
	{
		audio::file *file;
		ALuint       buffer;
		unsigned     refcount;
	};

	struct device_wrapper
	{
		ALCdevice *device;

		device_wrapper() : device(0) {}
		void reset(ALCdevice *n)
		{
			if (device != 0)
				alcCloseDevice(device);

			device = n;
		}

		~device_wrapper()
		{
			if (device != 0)
				alcCloseDevice(device);
		}
	};

	struct context_wrapper
	{
		ALCcontext *context;

		context_wrapper() : context(0) {}
		void reset(ALCcontext *n)
		{
			if (context != 0)
				alcDestroyContext(context);

			context = n;
		}

		~context_wrapper()
		{
			if (context != 0)
				alcDestroyContext(context);
		}
	};

	typedef std::vector<buffer_map>   buffer_map_container_type;
	typedef std::list<stream_sound *> stream_sound_container_type;

	stream_sound_container_type stream_sounds;
	math::vector3               listener_pos_;
	audio::sound_angle          listener_angle_;
	buffer_map_container_type   buffer_map_;
	device_wrapper              device;
	context_wrapper             context;

	void check(const string &);
public:
	player();

	void register_stream_sound(stream_sound *p) { stream_sounds.push_back(p); } 
	void unregister_stream_sound(stream_sound *p) { stream_sounds.remove(p); }

	ALuint register_nonstream_sound(audio::file_ptr);
	void unregister_nonstream_sound(ALuint);

	math::vector3 listener_pos() const { return listener_pos_; }
	void listener_pos(const math::vector3 &);
	const audio::sound_angle listener_angle() const { return listener_angle_; }
	void listener_angle(const audio::sound_angle &);
		
	const audio::sound_ptr create_nonstream_sound(audio::file_ptr);
	const audio::sound_ptr create_stream_sound(audio::file_ptr);
	void update();
};

}
}

#endif 
