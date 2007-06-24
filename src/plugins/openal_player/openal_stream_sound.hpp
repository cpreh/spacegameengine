#ifndef SGE_OPENAL_STREAM_SOUND_INCLUDED
#define SGE_OPENAL_STREAM_SOUND_INCLUDED

#include "../../audio/audio_player/sound.hpp"
#include "openal_player.hpp"

namespace sge
{
class openal_stream_sound : public sound
{
	openal_player &player_;
	sge::shared_ptr<sge::audio_file> audio_file_;
	std::size_t buffer_samples_;

	// OpenAL-Zeugs
	ALenum format_;
	ALuint al_buffers_[2];
	ALuint al_source_;

	bool loop_;
	sound_status status_;

	bool fill_buffer(ALuint);
	void check(const std::string &);

	public:
	openal_stream_sound(shared_ptr<audio_file>,openal_player &);
	~openal_stream_sound();
	void play(const bool);
	void toggle_pause();
	sound_status status() const { return status_; }
	void stop();
	void update();
};
}

#endif
