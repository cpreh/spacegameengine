#ifndef SGE_OPENAL_STREAM_SOUND_INCLUDED
#define SGE_OPENAL_STREAM_SOUND_INCLUDED

#include "../../audio/audio_player/sound.hpp"
#include "openal_player.hpp"
#include "../../math/vector.hpp"

namespace sge
{
namespace openal
{
class stream_sound : public sound
{
	player &                         player_;
	sge::shared_ptr<sge::audio_file> audio_file_;
	std::size_t                      buffer_samples_;
	math::vector3                    pos_;
	bool                             loop_,positional_;
	sound_status                     status_;

	// OpenAL-Zeugs
	ALenum format_;
	ALuint al_buffers_[2];
	ALuint al_source_;

	bool fill_buffer(ALuint);
	void check(const std::string &);
	void sync();
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
