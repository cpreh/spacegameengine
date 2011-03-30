#ifndef SGE_PROJECTILE_SHAPE_CIRCLE_HPP_INCLUDED
#define SGE_PROJECTILE_SHAPE_CIRCLE_HPP_INCLUDED

#include <sge/projectile/shape/base.hpp>
#include <sge/projectile/symbol.hpp>
#include <fcppt/noncopyable.hpp>
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
FCPPT_NONCOPYABLE(
	circle);
public:
	SGE_PROJECTILE_SYMBOL
	explicit
	circle(
		btScalar const radius);

	SGE_PROJECTILE_SYMBOL
	~circle();

	SGE_PROJECTILE_SYMBOL
	btCollisionShape &
	bullet_shape();

	SGE_PROJECTILE_SYMBOL
	btCollisionShape const &
	bullet_shape() const;
private:
	btSphereShape bullet_shape_;
};
}
}
}

#endif
