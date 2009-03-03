#include "../../objects/circle.hpp"
#include "../../system.hpp"
#include <sge/collision/sattelite.hpp>
#include <bullet/BulletCollision/CollisionShapes/btSphereShape.h>

sge::bullet::objects::circle::circle(
	system &s,
	collision::sattelite_ptr sat,
	collision::point const &_center,
	collision::point const &_speed,
	collision::unit const radius)
	: object(
			s,
			sat,
			shape_ptr(new btSphereShape(radius)),
			static_cast<unit>(1))
{
	center(_center);
	speed(_speed);
}

sge::collision::point const sge::bullet::objects::circle::speed() const
{
	return object::speed();
}

void sge::bullet::objects::circle::speed(sge::collision::point const &n)
{
	object::speed(n);
}

sge::collision::point const sge::bullet::objects::circle::center() const
{
	return object::pos();
}

void sge::bullet::objects::circle::center(sge::collision::point const &n)
{
	object::pos(n);
}
