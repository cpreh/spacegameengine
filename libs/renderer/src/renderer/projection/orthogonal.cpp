//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/renderer/matrix4.hpp>
#include <sge/renderer/scalar.hpp>
#include <sge/renderer/impl/projection/check_near_far.hpp>
#include <sge/renderer/projection/far.hpp>
#include <sge/renderer/projection/near.hpp>
#include <sge/renderer/projection/orthogonal.hpp>
#include <sge/renderer/projection/rect.hpp>
#include <fcppt/math/matrix/row.hpp>

sge::renderer::matrix4 sge::renderer::projection::orthogonal(
    sge::renderer::projection::rect const &_rect,
    sge::renderer::projection::near const _near,
    sge::renderer::projection::far const _far)
{
  sge::renderer::impl::projection::check_near_far(_near, _far);

  sge::renderer::scalar const one(1.F);
  sge::renderer::scalar const zero(0.F);
  sge::renderer::scalar const two(2.F);
  sge::renderer::scalar const left(_rect.left());
  sge::renderer::scalar const right(_rect.right());
  sge::renderer::scalar const top(_rect.top());
  sge::renderer::scalar const bottom(_rect.bottom());
  sge::renderer::scalar const near(_near.get());
  sge::renderer::scalar const far(_far.get());

  return sge::renderer::matrix4(
      fcppt::math::matrix::row(two / (right - left), zero, zero, (left + right) / (left - right)),
      fcppt::math::matrix::row(zero, two / (top - bottom), zero, (top + bottom) / (bottom - top)),
      fcppt::math::matrix::row(zero, zero, one / (far - near), near / (near - far)),
      fcppt::math::matrix::row(zero, zero, zero, one));
}
