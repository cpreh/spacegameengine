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
	audio::play_mode::type play_mode() const { return play_mode_; }
	virtual void play_mode(audio::play_mode::type);
	virtual void do_play() {}

	audio::point const pos() const { return pos_; }
	void pos(audio::point const &);
	audio::point const vel() const { return vel_; }
	void vel(audio::point const &);
	audio::unit attenuation() const { return attenuation_; }
	void attenuation(audio::unit);
	audio::unit rolloff() const { return rolloff_; }
	void rolloff(audio::unit);
	bool positional() const { return positional_; }
	void positional(bool);
	audio::point const direction() const { return direction_; }
	void direction(audio::point const &);
	audio::unit inner_cone_angle() const { return inner_cone_angle_; }
	void inner_cone_angle(audio::unit);
	audio::unit outer_cone_angle() const { return outer_cone_angle_; }
	void outer_cone_angle(audio::unit);
	~source();

	private:
	ALuint source_,buffer_;
	audio::play_mode::type play_mode_;
	mutable audio::sound_status::type status_;
	bool positional_;
	audio::point pos_;
	audio::point direction_;
	audio::point vel_;
	audio::unit attenuation_;
	audio::unit rolloff_;
	audio::unit inner_cone_angle_;
	audio::unit outer_cone_angle_;

	void init();
};
}
}

#endif
