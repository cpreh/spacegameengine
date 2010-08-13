#ifndef SGE_AUDIO_SOUND_BASE_HPP_INCLUDED
#define SGE_AUDIO_SOUND_BASE_HPP_INCLUDED

#include <sge/symbol.hpp>
#include <sge/class_symbol.hpp>
#include <sge/audio/scalar.hpp>
#include <sge/audio/sound/repeat.hpp>
#include <sge/audio/sound/play_status.hpp>
#include <fcppt/noncopyable.hpp>

namespace sge
{
namespace audio
{
namespace sound
{
class SGE_CLASS_SYMBOL base
{
FCPPT_NONCOPYABLE(base)
public:
	SGE_SYMBOL explicit
	base();

	virtual void 
	play(
		sge::audio::sound::repeat::type) = 0;

	virtual sge::audio::sound::repeat::type
	repeat() const = 0;

	virtual void 
	toggle_pause() = 0;

	virtual play_status::type 
	status() const = 0;

	virtual void 
	gain(
		scalar) = 0;

	virtual scalar 
	gain() const = 0;

	virtual void 
	pitch(
		scalar) = 0;

	virtual scalar 
	pitch() const = 0;

	virtual void 
	stop() = 0;

	virtual void
	update() = 0;

	SGE_SYMBOL virtual
	~base();
};
}
}
}

#endif
