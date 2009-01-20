#include "../../objects/circle.hpp"
#include "../../system.hpp"
#include <sge/collision/sattelite.hpp>
#include <bullet/BulletCollision/CollisionShapes/btSphereShape.h>

sge::bullet::objects::circle::circle(
	system &s,
	collision::sattelite_ptr sat,
	collision::unit const radius)
	: object(
			s,
			sat,
			shape_ptr(new btSphereShape(radius)),
			static_cast<unit>(1))
{
}
