#ifndef OPENAL_NONSTREAM_SOUND_INCLUDED
#define OPENAL_NONSTREAM_SOUND_INCLUDED

// OpenAL
#include <AL/al.h>
// Own stuff
#include "../../audio/audio_player/sound.hpp"
#include "openal_player.hpp"

namespace sge
{
namespace openal
{
class nonstream_sound : public sound
{
	player &      player_;
	mutable sound_status  status_;
	bool          loop_,positional_;
	math::vector3 pos_;

	ALuint al_buffer_;
	mutable ALuint al_source_;

	void check(const std::string &);
	void sync() const;
	public:
	nonstream_sound(shared_ptr<audio_file>,player &);
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
