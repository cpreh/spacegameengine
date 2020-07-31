//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_NOISE_PERLIN_OBJECT_IMPL_HPP_INCLUDED
#define SGE_NOISE_PERLIN_OBJECT_IMPL_HPP_INCLUDED

#include <sge/noise/perlin/object_decl.hpp>
#include <fcppt/use.hpp>
#include <fcppt/assert/optional_error.hpp>
#include <fcppt/cast/int_to_float.hpp>
#include <fcppt/container/grid/interpolate.hpp>
#include <fcppt/math/mod.hpp>
#include <fcppt/math/size_type.hpp>
#include <fcppt/math/dim/at.hpp>
#include <fcppt/math/vector/at.hpp>
#include <fcppt/math/vector/init.hpp>
#include <fcppt/random/variate.hpp>
#include <fcppt/random/distribution/basic.hpp>
#include <fcppt/random/distribution/parameters/uniform_real.hpp>


template<
	typename Float,
	fcppt::math::size_type N,
	typename Interpolator
>
template<
	typename Rng
>
sge::noise::perlin::object<
	Float,
	N,
	Interpolator
>::object(
	dim const &_size,
	Rng &_random_generator
)
:
	gradients_(
		[
			&_size,
			&_random_generator
		]{
			using
			uniform_real_distribution
			=
			fcppt::random::distribution::basic<
				fcppt::random::distribution::parameters::uniform_real<
					value_type
				>
			>;

			using
			distribution_parameters
			=
			typename
			uniform_real_distribution::param_type;

			using
			variate
			=
			fcppt::random::variate<
				Rng,
				uniform_real_distribution
			>;

			variate v{
				_random_generator,
				uniform_real_distribution{
					typename
					distribution_parameters::min{
						fcppt::literal<
							value_type
						>(
							-1
						)
					},
					typename
					distribution_parameters::sup{
						fcppt::literal<
							value_type
						>(
							1
						)
					}
				}
			};

			return
				grid_type{
					_size,
					[
						&v
					](
						typename
						grid_type::pos
					){
						return
							v();
					}
				};
		}()
	)
{
}

template<
	typename Float,
	fcppt::math::size_type N,
	typename Interpolator
>
typename
sge::noise::perlin::object<
	Float,
	N,
	Interpolator
>::value_type
sge::noise::perlin::object<
	Float,
	N,
	Interpolator
>::sample(
	vector_type const _v
) const
{
	return
		fcppt::container::grid::interpolate(
			gradients_,
			fcppt::math::vector::init<
				vector_type
			>(
				[
					&_v,
					this
				](
					auto const _index
				)
				{
					FCPPT_USE(
						_index
					);

					using
					index
					=
					decltype(
						_index
					);

					value_type const current_dimension{
						fcppt::cast::int_to_float<
							value_type
						>(
							fcppt::math::dim::at<
								index::value
							>(
								gradients_.size()
							)
						)
					};

					value_type const temp{
						FCPPT_ASSERT_OPTIONAL_ERROR(
							fcppt::math::mod(
								fcppt::math::vector::at<
									index::value
								>(
									_v
								),
								current_dimension
							)
						)
					};

					return
						FCPPT_ASSERT_OPTIONAL_ERROR(
							fcppt::math::mod(
								temp
								+
								current_dimension,
								current_dimension
							)
						);
				}
			),
			Interpolator()
		);
}

#endif

