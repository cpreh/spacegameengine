//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/opengl/convert/projection.hpp>
#include <sge/renderer/matrix4.hpp>
#include <sge/renderer/scalar.hpp>
#include <fcppt/math/matrix/arithmetic.hpp>
#include <fcppt/math/matrix/scaling.hpp>
#include <fcppt/math/matrix/translation.hpp>

sge::renderer::matrix4 sge::opengl::convert::projection(sge::renderer::matrix4 const &_matrix)
{
  sge::renderer::scalar const one{1.0F};
  sge::renderer::scalar const two{0.5F};
  sge::renderer::scalar const zero{0.0F};

  return fcppt::math::matrix::translation(zero, zero, -one) *
         fcppt::math::matrix::scaling(one, one, two) * _matrix;
}
