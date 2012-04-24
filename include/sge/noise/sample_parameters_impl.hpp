#ifndef SGE_NOISE_SAMPLE_PARAMETERS_IMPL_HPP_INCLUDED
#define SGE_NOISE_SAMPLE_PARAMETERS_IMPL_HPP_INCLUDED

#include <sge/noise/sample_parameters_decl.hpp>

template<
	typename Noise
>
sge::noise::sample_parameters<
	Noise
>::sample_parameters(
	position_type const &_position,
	amplitude_type const &_amplitude,
	frequency_type const &_frequency,
	octaves_type const &_octaves)
:
	position_(
		_position),
	amplitude_(
		_amplitude),
	frequency_(
		_frequency),
	octaves_(
		_octaves)
{
}

template<
	typename Noise
>
typename
sge::noise::sample_parameters<
	Noise
>::position_type const
sge::noise::sample_parameters<
	Noise
>::position() const
{
	return position_;
}

template<
	typename Noise
>
typename
sge::noise::sample_parameters<
	Noise
>::frequency_type const
sge::noise::sample_parameters<
	Noise
>::frequency() const
{
	return frequency_;
}

template<
	typename Noise
>
typename
sge::noise::sample_parameters<
	Noise
>::amplitude_type const
sge::noise::sample_parameters<
	Noise
>::amplitude() const
{
	return amplitude_;
}

template<
	typename Noise
>
typename
sge::noise::sample_parameters<
	Noise
>::octaves_type const
sge::noise::sample_parameters<
	Noise
>::octaves() const
{
	return octaves_;
}

#endif
