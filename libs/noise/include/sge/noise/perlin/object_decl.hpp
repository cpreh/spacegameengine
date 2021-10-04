//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_NOISE_PERLIN_OBJECT_DECL_HPP_INCLUDED
#define SGE_NOISE_PERLIN_OBJECT_DECL_HPP_INCLUDED

#include <sge/noise/perlin/object_fwd.hpp>
#include <fcppt/reference_fwd.hpp>
#include <fcppt/container/grid/object_impl.hpp>
#include <fcppt/math/size_type.hpp>
#include <fcppt/math/vector/static_fwd.hpp>
#include <fcppt/preprocessor/pure.hpp>
#include <fcppt/config/external_begin.hpp>
#include <type_traits>
#include <fcppt/config/external_end.hpp>


namespace sge::noise::perlin
{

template<
	typename Float,
	fcppt::math::size_type N,
	typename Interpolator
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
	value_type
	=
	Float;

	using
	grid_type
	=
	fcppt::container::grid::object<
		value_type,
		N
	>;

	using
	vector_type
	=
	fcppt::math::vector::static_<
		value_type,
		N
	>;

	using
	dim
	=
	typename
	grid_type::dim;

	template<
		typename Rng
	>
	object(
		dim const &,
		fcppt::reference<
			Rng
		>
	);

	[[nodiscard]]
	value_type
	sample(
		vector_type
	) const
	FCPPT_PP_PURE;
private:
	grid_type gradients_;
};

}

#endif

