/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2015 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#ifndef SGE_NOISE_SAMPLE_HPP_INCLUDED
#define SGE_NOISE_SAMPLE_HPP_INCLUDED

#include <sge/noise/sample_parameters.hpp>
#include <fcppt/config/external_begin.hpp>
#include <cmath>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace noise
{

template<
	typename Noise
>
typename Noise::value_type
sample(
	Noise &_noise,
	sample_parameters<
		Noise
	> const &_parameters)
{
	typedef
	typename Noise::value_type
	result_type;

	double sum = 0.0;

	double const
		amp =
			static_cast<
				double
			>(
				_parameters.amplitude().get()
			),
		freq =
			static_cast<
				double
			>(
				_parameters.frequency().get()
			),
		octaves =
			static_cast<
				double
			>(
				_parameters.octaves().get()
			),
		scaling =
			std::pow(2.0, octaves) /
			(std::pow(2.0, octaves) - 1.0);

	for (
		typename sge::noise::sample_parameters<Noise>::octaves_type i(1u);
		i <= _parameters.octaves();
		++i
	)
	{
			sum +=
				std::pow(
					0.5,
					static_cast<
						double
					>(
						i.get()
					)
				) *
				static_cast<double>(
				  _noise.sample(
					static_cast<result_type>(
						std::pow(
							2.0,
							static_cast<
								double
							>(
								i.get()
							)
						)
						* freq)
					* _parameters.position().get()
				));
	}

	return
		static_cast<
			result_type
		>(
			sum *
			amp *
			scaling
		);
}

}
}

#endif
