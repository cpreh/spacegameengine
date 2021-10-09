//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_CAMERA_TRACKING_ALEXA_LERP_HPP_INCLUDED
#define SGE_CAMERA_TRACKING_ALEXA_LERP_HPP_INCLUDED

#include <sge/camera/tracking/alexa/add.hpp>
#include <sge/camera/tracking/alexa/multiply.hpp>
#include <fcppt/literal.hpp>
#include <fcppt/math/size_type.hpp>
#include <fcppt/math/matrix/object_impl.hpp>
#include <fcppt/math/matrix/static.hpp>

namespace sge::camera::tracking::alexa
{

template <typename T, fcppt::math::size_type N, typename S1, typename S2>
fcppt::math::matrix::static_<T, N, N> lerp(
    T const _value,
    fcppt::math::matrix::object<T, N, N, S1> const &_a,
    fcppt::math::matrix::object<T, N, N, S2> const &_b)
{
  return sge::camera::tracking::alexa::add(
      sge::camera::tracking::alexa::multiply(fcppt::literal<T>(1) - _value, _a),
      sge::camera::tracking::alexa::multiply(_value, _b));
}

}

#endif
