//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_NOISE_SIMPLEX_OBJECT_DECL_HPP_INCLUDED
#define SGE_NOISE_SIMPLEX_OBJECT_DECL_HPP_INCLUDED

#include <sge/noise/simplex/object_fwd.hpp>
#include <sge/noise/simplex/width.hpp>
#include <fcppt/math/size_type.hpp>
#include <fcppt/math/matrix/static_fwd.hpp>
#include <fcppt/math/vector/static.hpp>
#include <fcppt/config/external_begin.hpp>
#include <array>
#include <cstddef>
#include <type_traits>
#include <vector>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace noise
{
namespace simplex
{

template<
	typename Float,
	fcppt::math::size_type N
>
class object
{
	static_assert(
		std::is_floating_point<
			Float
		>::value,
		"Float must be a floating-point type"
	);
public:
	typedef
	fcppt::math::vector::static_<
		Float,
		N
	>
	vector_type;

	typedef
	Float
	value_type;

	explicit
	object(
		sge::noise::simplex::width const &);

	Float
	sample(
		vector_type const &);
private:
	typedef
	fcppt::math::size_type
	index_type;

	typedef
	std::vector<
		index_type
	> index_container;

	typedef
	fcppt::math::matrix::static_<
		Float,
		N,
		N
	>
	matrix;

	typedef
	std::array<vector_type,2u*N>
	gradient_array;

	index_container perm_;
	gradient_array gradients_;

	std::size_t
	mod(
		long int const &a,
		std::size_t const &b);

	std::size_t
	index(
		vector_type const &vec);

	typedef std::array<
		vector_type,
		N + 1
	> corner_array;

	corner_array
	corners(
		vector_type point);

	Float
	stretch_factor();

	Float
	inv_factor();

	matrix
	stretch_m();

	matrix
	inv_m();

	Float
	contrib(
		vector_type const &v,
		vector_type const &intv);
};

}
}
}

#endif
