#include <sge/projectile/shape/circle.hpp>

sge::projectile::shape::circle::circle(
	btScalar const _radius)
:
	base(),
	bullet_shape_(
		_radius)
{
}

btCollisionShape &
sge::projectile::shape::circle::bullet_shape()
{
	return bullet_shape_;
}

btCollisionShape const &
sge::projectile::shape::circle::bullet_shape() const
{
	return bullet_shape_;
}
