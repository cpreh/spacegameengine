#ifndef SGE_NOISE_SAMPLE_PARAMETERS_DECL_HPP_INCLUDED
#define SGE_NOISE_SAMPLE_PARAMETERS_DECL_HPP_INCLUDED

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
FCPPT_NONASSIGNABLE(
	sample_parameters);
public:
	FCPPT_MAKE_STRONG_TYPEDEF(
		typename Noise::vector_type,
		position_type);

	FCPPT_MAKE_STRONG_TYPEDEF(
		typename Noise::value_type,
		amplitude_type);

	FCPPT_MAKE_STRONG_TYPEDEF(
		typename Noise::value_type,
		frequency_type);

	FCPPT_MAKE_STRONG_TYPEDEF(
		unsigned,
		octaves_type);

	explicit
	sample_parameters(
		position_type const &,
		amplitude_type const &,
		frequency_type const &,
		octaves_type const &);

	position_type const
	position() const;

	frequency_type const
	frequency() const;

	amplitude_type const
	amplitude() const;

	octaves_type const
	octaves() const;

private:
	position_type const &position_;
	amplitude_type const &amplitude_;
	frequency_type const &frequency_;
	octaves_type const octaves_;
};

}
}

#endif
