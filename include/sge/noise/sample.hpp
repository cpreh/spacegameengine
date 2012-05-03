#ifndef SGE_NOISE_SAMPLE_HPP_INCLUDED
#define SGE_NOISE_SAMPLE_HPP_INCLUDED

#include <sge/noise/sample_parameters.hpp>
#include <cmath>

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
