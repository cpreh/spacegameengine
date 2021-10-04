//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_NOISE_SIMPLEX_OBJECT_DECL_HPP_INCLUDED
#define SGE_NOISE_SIMPLEX_OBJECT_DECL_HPP_INCLUDED

#include <sge/noise/simplex/object_fwd.hpp>
#include <sge/noise/simplex/width.hpp>
#include <fcppt/array/object_impl.hpp>
#include <fcppt/math/size_type.hpp>
#include <fcppt/math/matrix/static_fwd.hpp>
#include <fcppt/math/vector/static.hpp>
#include <fcppt/config/external_begin.hpp>
#include <cstddef>
#include <type_traits>
#include <vector>
#include <fcppt/config/external_end.hpp>


namespace sge::noise::simplex
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
	using
	vector_type
	=
	fcppt::math::vector::static_<
		Float,
		N
	>;

	using
	value_type
	=
	Float;

	explicit
	object(
		sge::noise::simplex::width const &
	);

	[[nodiscard]]
	Float
	sample(
		vector_type const &
	);
private:
	using
	index_type
	=
	fcppt::math::size_type;

	using
	index_container
	=
	std::vector<
		index_type
	>;

	using
	matrix
	=
	fcppt::math::matrix::static_<
		Float,
		N,
		N
	>;

	using
	gradient_array
	=
	fcppt::array::object<
		vector_type,
		2U*N
	>;

	index_container perm_;
	gradient_array gradients_;

	[[nodiscard]]
	std::size_t
	mod(
		long int const &a, // NOLINT(google-runtime-int)
		std::size_t const &b
	);

	[[nodiscard]]
	std::size_t
	index(
		vector_type const &vec
	);

	using
	corner_array
	=
	fcppt::array::object<
		vector_type,
		N + 1
	>;

	[[nodiscard]]
	corner_array
	corners(
		vector_type point
	);

	[[nodiscard]]
	Float
	stretch_factor();

	[[nodiscard]]
	Float
	inv_factor();

	[[nodiscard]]
	matrix
	stretch_m();

	[[nodiscard]]
	matrix
	inv_m();

	[[nodiscard]]
	Float
	contrib(
		vector_type const &v,
		vector_type const &intv
	);
};

}

#endif
