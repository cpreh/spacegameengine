//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_CAMERA_TRACKING_ALEXA_LOGARITHM_HPP_INCLUDED
#define SGE_CAMERA_TRACKING_ALEXA_LOGARITHM_HPP_INCLUDED

#include <fcppt/literal.hpp>
#include <fcppt/math/size_type.hpp>
#include <fcppt/math/matrix/logarithm.hpp>
#include <fcppt/math/matrix/object_impl.hpp>
#include <fcppt/math/matrix/static.hpp>

namespace sge::camera::tracking::alexa
{

template <typename T, fcppt::math::size_type N, typename S>
fcppt::math::matrix::static_<T, N, N>
logarithm(fcppt::math::matrix::object<T, N, N, S> const &_matrix)
{
  return fcppt::math::matrix::logarithm(
      _matrix,
      fcppt::literal<T>(
          1.0e-4 // NOLINT(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
          ),
      fcppt::literal<T>(
          1.0e-9 // NOLINT(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
          ),
      fcppt::literal<T>(
          1.0e-6 // NOLINT(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
          ));
}

}

#endif
