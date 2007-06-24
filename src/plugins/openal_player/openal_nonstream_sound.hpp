#ifndef OPENAL_NONSTREAM_SOUND_INCLUDED
#define OPENAL_NONSTREAM_SOUND_INCLUDED

// OpenAL
#include <AL/al.h>
// Own stuff
#include "../../audio/audio_player/sound.hpp"
#include "openal_player.hpp"

namespace sge
{
class openal_nonstream_sound : public sound
{
	openal_player &player_;
	ALuint al_buffer_;
	ALuint al_source_;
	sound_status status_;
	bool loop_;

	void check(const std::string &);
	public:
	openal_nonstream_sound(shared_ptr<audio_file>,openal_player &);
	~openal_nonstream_sound();
	void play(const bool);
	void toggle_pause();
	sound_status status() const { return status_; };
	void stop();
	void update();
};
}

#endif
