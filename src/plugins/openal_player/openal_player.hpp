#ifndef SGE_OPENAL_PLAYER_INCLUDED
#define SGE_OPENAL_PLAYER_INCLUDED

// C++
#include <list>
// OpenAL
#include <AL/al.h>
#include <AL/alc.h>
// Own stuff
#include "../../audio/audio_player/audio_player.hpp"
#include "../../audio/audio_player/sound_angle.hpp"

namespace sge
{
namespace openal
{
class stream_sound;
class player : public audio_player
{
	struct buffer_map
	{
		audio_file * file;
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
	sound_angle                 listener_angle_;
	buffer_map_container_type   buffer_map_;
	device_wrapper              device;
	context_wrapper             context;

	void check(const std::string &);
	public:
		player();

		void register_stream_sound(stream_sound *p) { stream_sounds.push_back(p); } 
		void unregister_stream_sound(stream_sound *p) { stream_sounds.remove(p); }

		ALuint register_nonstream_sound(shared_ptr<audio_file>);
		void unregister_nonstream_sound(ALuint);

		math::vector3 listener_pos() const { return listener_pos_; }
		void listener_pos(const math::vector3 &);
		sound_angle listener_angle() const { return listener_angle_; }
		void listener_angle(const sound_angle &);
		
		shared_ptr<sound> create_nonstream_sound(shared_ptr<audio_file> _audio_file);
		shared_ptr<sound> create_stream_sound(shared_ptr<audio_file> _audio_file);
		void update();
};
}
}

#endif 
