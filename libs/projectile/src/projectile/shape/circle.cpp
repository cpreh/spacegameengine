//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/projectile/scalar.hpp>
#include <sge/projectile/shape/base.hpp>
#include <sge/projectile/shape/circle.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/unique_ptr_to_base.hpp>
#include <fcppt/config/external_begin.hpp>
#include <BulletCollision/CollisionShapes/btCollisionShape.h>
#include <BulletCollision/CollisionShapes/btSphereShape.h>
#include <fcppt/config/external_end.hpp>

sge::projectile::shape::circle::circle(sge::projectile::scalar const _radius)
    : sge::projectile::shape::base(),
      bullet_shape_(fcppt::unique_ptr_to_base<btCollisionShape>(
          fcppt::make_unique_ptr<btSphereShape>(_radius)))
{
}

btCollisionShape &sge::projectile::shape::circle::bullet_shape() { return *bullet_shape_; }

btCollisionShape const &sge::projectile::shape::circle::bullet_shape() const
{
  return *bullet_shape_;
}

sge::projectile::shape::circle::~circle() = default;
