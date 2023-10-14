//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_NOISE_PERLIN_OBJECT_IMPL_HPP_INCLUDED
#define SGE_NOISE_PERLIN_OBJECT_IMPL_HPP_INCLUDED

#include <sge/core/exception.hpp>
#include <sge/noise/perlin/object_decl.hpp> // IWYU pragma: export
#include <fcppt/reference_impl.hpp>
#include <fcppt/text.hpp>
#include <fcppt/cast/int_to_float.hpp>
#include <fcppt/container/grid/interpolate.hpp>
#include <fcppt/math/mod.hpp>
#include <fcppt/math/size_constant.hpp>
#include <fcppt/math/size_type.hpp>
#include <fcppt/math/dim/at.hpp>
#include <fcppt/math/dim/contents.hpp>
#include <fcppt/math/vector/at.hpp>
#include <fcppt/math/vector/init.hpp>
#include <fcppt/random/variate.hpp>
#include <fcppt/random/distribution/basic.hpp>
#include <fcppt/random/distribution/parameters/uniform_real.hpp>

template <typename Float, fcppt::math::size_type N, typename Interpolator>
template <typename Rng>
sge::noise::perlin::object<Float, N, Interpolator>::object(
    dim const &_size, fcppt::reference<Rng> const _random_generator)
    : gradients_(
          [&_size, &_random_generator]
          {
            using uniform_real_distribution = fcppt::random::distribution::basic<
                fcppt::random::distribution::parameters::uniform_real<value_type>>;

            using distribution_parameters = typename uniform_real_distribution::param_type;

            using variate = fcppt::random::variate<Rng, uniform_real_distribution>;

            variate v{
                _random_generator,
                uniform_real_distribution{
                    typename distribution_parameters::min{fcppt::literal<value_type>(-1)},
                    typename distribution_parameters::sup{fcppt::literal<value_type>(1)}}};

            return grid_type{_size, [&v](typename grid_type::pos) { return v(); }};
          }())
{
  if (fcppt::math::dim::contents(_size) == 0U)
  {
    throw sge::core::exception{FCPPT_TEXT("noise::perlin: Invalid size of 0!")};
  }
}

template <typename Float, fcppt::math::size_type N, typename Interpolator>
typename sge::noise::perlin::object<Float, N, Interpolator>::value_type
sge::noise::perlin::object<Float, N, Interpolator>::sample(vector_type const _v) const
{
  return fcppt::container::grid::interpolate(
      gradients_,
      fcppt::math::vector::init<vector_type>(
          [&_v, this]<fcppt::math::size_type Index>(fcppt::math::size_constant<Index>)
          {
            value_type const current_dimension{fcppt::cast::int_to_float<value_type>(
                fcppt::math::dim::at<Index>(gradients_.size()))};

            value_type const temp{
                fcppt::math::mod(fcppt::math::vector::at<Index>(_v), current_dimension)
                    .get_unsafe()};

            return fcppt::math::mod(temp + current_dimension, current_dimension).get_unsafe();
          }),
      Interpolator());
}

#endif
