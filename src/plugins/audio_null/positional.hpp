#ifndef SGE_PLUGINS_AUDIO_NULL_POSITIONAL_HPP_INCLUDED
#define SGE_PLUGINS_AUDIO_NULL_POSITIONAL_HPP_INCLUDED

#include <sge/audio/sound/positional.hpp>

namespace sge
{
namespace audio_null
{
class positional
:
	public sge::audio::sound::positional
{
public:
	void 
	play(
		sge::audio::sound::repeat::type) {}

	sge::audio::sound::repeat::type
	repeat() const { return sge::audio::sound::repeat::once; }

	void 
	toggle_pause() {}

	audio::sound::play_status::type 
	status() const { return audio::sound::play_status::stopped; }

	void 
	stop() {}

	void
	update() {}

	audio::vector const 
	position() const { return audio::vector(); }

	void 
	position(
		audio::vector const &) {}

	audio::vector const 
	linear_velocity() const { return audio::vector(); }

	void 
	linear_velocity(
		audio::vector const &) { }

	void 
	gain(
		audio::scalar) {}

	audio::scalar 
	gain() const { return audio::scalar(); }

	void 
	pitch(
		audio::scalar) {}

	audio::scalar 
	pitch() const { return audio::scalar(); }

	void 
	rolloff(
		audio::scalar) {}

	audio::scalar 
	rolloff() const { return audio::scalar(); }

	void 
	direction(
		audio::vector const &) {}

	audio::vector const 
	direction() const { return audio::vector(); } 

	void 
	inner_cone_angle(
		audio::scalar) {}

	audio::scalar 
	inner_cone_angle() const { return audio::scalar(); }

	void 
	outer_cone_angle(
		audio::scalar) {}

	audio::scalar 
	outer_cone_angle() const { return audio::scalar(); }
};
}
}

#endif
