/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2012 Carl Philipp Reh (sefi@s-e-f-i.de)

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/


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
