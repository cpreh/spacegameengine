//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_NOISE_SAMPLE_HPP_INCLUDED
#define SGE_NOISE_SAMPLE_HPP_INCLUDED

#include <sge/noise/sample_parameters.hpp>
#include <fcppt/reference_impl.hpp>
#include <fcppt/config/external_begin.hpp>
#include <cmath>
#include <fcppt/config/external_end.hpp>


namespace sge::noise
{

template<
	typename Noise
>
typename
Noise::value_type
sample(
	fcppt::reference<
		Noise
	> const _noise,
	sample_parameters<
		Noise
	> const &_parameters
)
{
	using
	result_type
	=
	typename Noise::value_type;

	double sum = 0.0;

	double const amp{
		static_cast<
			double
		>(
			_parameters.amplitude().get()
		)
	};
	double const freq{
		static_cast<
			double
		>(
			_parameters.frequency().get()
		)
	};
	double const octaves{
		static_cast<
			double
		>(
			_parameters.octaves().get()
		)
	};
	double const scaling{
		std::pow(2.0, octaves) /
		(std::pow(2.0, octaves) - 1.0)
	};

	for (
		typename sge::noise::sample_parameters<Noise>::octaves_type i(1U);
		i <= _parameters.octaves();
		++i
	)
	{
			sum +=
				std::pow(
					0.5, // NOLINT(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
					static_cast<
						double
					>(
						i.get()
					)
				) *
				static_cast<double>(
					_noise.get().sample(
						static_cast<result_type>(
							std::pow(
								2.0, // NOLINT(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
								static_cast<
									double
								>(
									i.get()
								)
							)
							* freq)
						* _parameters.position().get()
					)
				);
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

#endif
