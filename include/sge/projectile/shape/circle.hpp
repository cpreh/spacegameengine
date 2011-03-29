#ifndef SGE_PROJECTILE_SHAPE_CIRCLE_HPP_INCLUDED
#define SGE_PROJECTILE_SHAPE_CIRCLE_HPP_INCLUDED

#include <sge/projectile/shape/base.hpp>
#include <BulletCollision/CollisionShapes/btSphereShape.h>

namespace sge
{
namespace projectile
{
namespace shape
{
class circle
:
	public base
{
public:
	explicit
	circle(
		btScalar const radius);

	btCollisionShape &
	bullet_shape();

	btCollisionShape const &
	bullet_shape() const;
private:
	btSphereShape bullet_shape_;
};
}
}
}

#endif
