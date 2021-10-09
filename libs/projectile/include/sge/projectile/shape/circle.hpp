//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_PROJECTILE_SHAPE_CIRCLE_HPP_INCLUDED
#define SGE_PROJECTILE_SHAPE_CIRCLE_HPP_INCLUDED

#include <sge/core/detail/class_symbol.hpp>
#include <sge/projectile/scalar.hpp>
#include <sge/projectile/detail/symbol.hpp>
#include <sge/projectile/shape/base.hpp>
#include <fcppt/nonmovable.hpp>
#include <fcppt/unique_ptr_impl.hpp>

class btCollisionShape;

namespace sge::projectile::shape
{
class SGE_CORE_DETAIL_CLASS_SYMBOL circle : public sge::projectile::shape::base
{
  FCPPT_NONMOVABLE(circle);

public:
  SGE_PROJECTILE_DETAIL_SYMBOL
  explicit circle(sge::projectile::scalar radius);

  [[nodiscard]]
  // No symbol needed here
  btCollisionShape &
  bullet_shape() override;

  [[nodiscard]] btCollisionShape const &bullet_shape() const override;

  SGE_PROJECTILE_DETAIL_SYMBOL
  ~circle() override;

private:
  fcppt::unique_ptr<btCollisionShape> const bullet_shape_;
};
}

#endif
