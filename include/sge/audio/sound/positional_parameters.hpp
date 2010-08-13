#ifndef SGE_AUDIO_SOUND_POSITIONAL_PARAMETERS_HPP_INCLUDED
#define SGE_AUDIO_SOUND_POSITIONAL_PARAMETERS_HPP_INCLUDED

#include <sge/class_symbol.hpp>
#include <sge/symbol.hpp>
#include <sge/audio/vector.hpp>
#include <sge/audio/scalar.hpp>
#include <fcppt/math/vector/basic_impl.hpp>

namespace sge
{
namespace audio
{
namespace sound
{
class SGE_CLASS_SYMBOL positional_parameters
{
public:
	SGE_SYMBOL explicit
	positional_parameters();

	SGE_SYMBOL vector const &
	position() const;

	SGE_SYMBOL positional_parameters &
	position(
		vector const &);

	SGE_SYMBOL vector const &
	linear_velocity() const;

	SGE_SYMBOL positional_parameters &
	linear_velocity(
		vector const &);

	SGE_SYMBOL scalar const &
	gain() const;

	SGE_SYMBOL positional_parameters &
	gain(
		scalar const &);

	SGE_SYMBOL scalar const &
	rolloff() const;

	SGE_SYMBOL positional_parameters &
	rolloff(
		scalar const &);

	SGE_SYMBOL vector const &
	direction() const;

	SGE_SYMBOL positional_parameters &
	direction(
		vector const &);

	SGE_SYMBOL scalar const &
	inner_cone_angle() const;

	SGE_SYMBOL positional_parameters &
	inner_cone_angle(
		scalar const &);

	SGE_SYMBOL scalar const &
	outer_cone_angle() const;

	SGE_SYMBOL positional_parameters &
	outer_cone_angle(
		scalar const &);
private:
	vector position_;
	vector linear_velocity_;
	scalar gain_;
	scalar rolloff_;
	vector direction_;
	scalar inner_cone_angle_;
	scalar outer_cone_angle_;
};
}
}
}

#endif
