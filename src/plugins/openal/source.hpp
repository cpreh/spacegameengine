#ifndef SGE_OPENAL_SOURCE_HPP_INCLUDED
#define SGE_OPENAL_SOURCE_HPP_INCLUDED

#include "openal.hpp"
#include <sge/audio/sound.hpp>

namespace sge
{
namespace openal
{
class source : public audio::sound
{
	public:
	explicit source();
	explicit source(ALuint);
	ALuint alsource() const { return source_; }
	ALuint albuffer() const { return buffer_; }
	void sync() const;
	void play(audio::play_mode::type);
	void toggle_pause();
	audio::sound_status::type status() const;
	void stop();
	audio::point const pos() const { return pos_; }
	audio::point const vel() const { return vel_; }
	void pos(audio::point const &);
	void vel(audio::point const &);
	bool positional() const { return positional_; }
	void positional(bool);
	audio::play_mode::type play_mode() const { return play_mode_; }
	virtual void play_mode(audio::play_mode::type);
	virtual void do_play() {}
	~source();

	private:
	ALuint source_,buffer_;
	audio::play_mode::type play_mode_;
	mutable audio::sound_status::type status_;
	bool positional_;
	audio::point pos_;
	audio::point vel_;
};
}
}

#endif
