//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_NOISE_SAMPLE_PARAMETERS_IMPL_HPP_INCLUDED
#define SGE_NOISE_SAMPLE_PARAMETERS_IMPL_HPP_INCLUDED

#include <sge/noise/sample_parameters_decl.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>


template<
	typename Noise
>
sge::noise::sample_parameters<
	Noise
>::sample_parameters(
	position_type _position,
	amplitude_type const &_amplitude,
	frequency_type const &_frequency,
	octaves_type const &_octaves)
:
	position_(
		std::move(
			_position
		)
	),
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
>::position_type
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
>::frequency_type
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
>::amplitude_type
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
>::octaves_type
sge::noise::sample_parameters<
	Noise
>::octaves() const
{
	return octaves_;
}

#endif
