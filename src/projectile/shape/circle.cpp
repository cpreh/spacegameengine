#include <sge/projectile/shape/circle.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <BulletCollision/CollisionShapes/btSphereShape.h>

sge::projectile::shape::circle::circle(
	scalar const _radius)
:
	base(),
	bullet_shape_(
		fcppt::make_unique_ptr<btSphereShape>(
			_radius))
{
}

btCollisionShape &
sge::projectile::shape::circle::bullet_shape()
{
	return *bullet_shape_;
}

btCollisionShape const &
sge::projectile::shape::circle::bullet_shape() const
{
	return *bullet_shape_;
}

sge::projectile::shape::circle::~circle() {}
