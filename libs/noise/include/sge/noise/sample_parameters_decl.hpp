//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_NOISE_SAMPLE_PARAMETERS_DECL_HPP_INCLUDED
#define SGE_NOISE_SAMPLE_PARAMETERS_DECL_HPP_INCLUDED

#include <fcppt/make_strong_typedef.hpp>
#include <fcppt/strong_typedef.hpp>


namespace sge
{
namespace noise
{

template<
	typename Noise
>
class sample_parameters
{
public:
	FCPPT_MAKE_STRONG_TYPEDEF(
		typename
		Noise::vector_type,
		position_type
	);

	FCPPT_MAKE_STRONG_TYPEDEF(
		typename
		Noise::value_type,
		amplitude_type
	);

	FCPPT_MAKE_STRONG_TYPEDEF(
		typename
		Noise::value_type,
		frequency_type
	);

	FCPPT_MAKE_STRONG_TYPEDEF(
		unsigned,
		octaves_type
	);

	sample_parameters(
		position_type const &,
		amplitude_type const &,
		frequency_type const &,
		octaves_type const &
	);

	position_type
	position() const;

	frequency_type
	frequency() const;

	amplitude_type
	amplitude() const;

	octaves_type
	octaves() const;
private:
	position_type position_;

	amplitude_type amplitude_;

	frequency_type frequency_;

	octaves_type octaves_;
};

}
}

#endif
