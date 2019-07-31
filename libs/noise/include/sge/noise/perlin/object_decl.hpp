//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_NOISE_PERLIN_OBJECT_DECL_HPP_INCLUDED
#define SGE_NOISE_PERLIN_OBJECT_DECL_HPP_INCLUDED

#include <sge/noise/perlin/object_fwd.hpp>
#include <fcppt/container/grid/object_impl.hpp>
#include <fcppt/math/size_type.hpp>
#include <fcppt/math/vector/static_fwd.hpp>
#include <fcppt/preprocessor/pure.hpp>
#include <fcppt/config/external_begin.hpp>
#include <type_traits>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace noise
{
namespace perlin
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
	typedef
	Float
	value_type;

	typedef
	fcppt::container::grid::object<
		value_type,
		N
	>
	grid_type;

	typedef
	fcppt::math::vector::static_<
		value_type,
		N
	>
	vector_type;

	typedef
	typename
	grid_type::dim
	dim;

	template<
		typename Rng
	>
	object(
		dim const &,
		Rng &
	);

	value_type
	sample(
		vector_type
	) const
	FCPPT_PP_PURE;
private:
	grid_type gradients_;
};

}
}
}

#endif

