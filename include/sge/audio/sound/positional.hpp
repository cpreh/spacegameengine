#ifndef SGE_AUDIO_SOUND_POSITIONAL_HPP_INCLUDED
#define SGE_AUDIO_SOUND_POSITIONAL_HPP_INCLUDED

#include <sge/class_symbol.hpp>
#include <sge/audio/sound/base.hpp>
#include <sge/audio/vector.hpp>
#include <sge/audio/scalar.hpp>

namespace sge
{
namespace audio
{
namespace sound
{
class SGE_CLASS_SYMBOL positional
:
	public base
{
public:
	virtual vector const 
	position() const = 0;

	virtual void 
	position(
		vector const &) = 0;

	virtual vector const 
	linear_velocity() const = 0;

	virtual void 
	linear_velocity(
		vector const &) = 0;

	virtual void 
	attenuation(
		scalar) = 0;

	virtual scalar 
	attenuation() const = 0;

	virtual void 
	rolloff(
		scalar) = 0;

	virtual scalar 
	rolloff() const = 0;

	virtual void 
	direction(
		vector const &) = 0;

	virtual vector const 
	direction() const = 0;

	virtual void 
	inner_cone_angle(
		scalar) = 0;

	virtual scalar 
	inner_cone_angle() const = 0;

	virtual void 
	outer_cone_angle(
		scalar) = 0;

	virtual scalar 
	outer_cone_angle() const = 0;
};
}
}
}

#endif
