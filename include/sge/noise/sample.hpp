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
	> &_parameters)
{
	typedef
	typename Noise::value_type
	result_type;

	double result = 0.0;

	double const
		amp =
			static_cast<
				double
			>(
				_parameters.amplitude()
			),
		freq =
			static_cast<
				double
			>(
				_parameters.frequency()
			);

	for (
		typename sge::noise::sample_parameters<Noise>::octaves_type i(0u);
		i < _parameters.octaves();
		++i
	)
		result +=
			std::pow(
				0.5,
				static_cast<
					double
				>(
					i.get()
				)
			)
			* amp
			* _noise.sample(
				std::pow(
					2.0,
					static_cast<
						double
					>(
						i.get()
					)
				)
				* freq
				* _parameters.position()
			);

	return
		static_cast<
			result_type
		>(
			result
		);
}

}
}

#endif
