#ifndef SGE_NOISE_SAMPLE_PARAMETERS_HPP_INCLUDED
#define SGE_NOISE_SAMPLE_PARAMETERS_HPP_INCLUDED

#include <sge/noise/sample_parameters_decl.hpp>

template<
	typename Noise
>
class sample_parameters
{
public:

	explicit
	sample_parameters(
		position_type &_position,
		amplitude_type &_amplitude,
		frequency_type &_frequency,
		octaves_type &_octaves)
	:
		position_(
			_position),
		amplitude_(
			_amplitude),
		frequency_(
			_frequency),
		octaves_(
			_octaves),
	{
	}

	position_type const;
	position() const
	{
		return position_;
	}

	frequency_type const
	frequency() const
	{
		return frequency_;
	}

	amplitude_type const
	amplitude() const
	{
		return amplitude_;
	}

	octaves_type const
	octaves() const
	{
		return octaves_;
	}

#endif
