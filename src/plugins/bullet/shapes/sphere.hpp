#ifndef SGE_BULLET_SHAPES_SPHERE_HPP_INCLUDED
#define SGE_BULLET_SHAPES_SPHERE_HPP_INCLUDED

#include "base.hpp"
#include "../unit.hpp"
#include "../world_fwd.hpp"
#include <sge/collision/shapes/sphere.hpp>
#include <BulletCollision/CollisionShapes/btSphereShape.h>

namespace sge
{
namespace bullet
{
namespace shapes
{
class sphere
:
	public base,
	public collision::shapes::sphere
{
public:
	sphere(
		collision::satellite_ptr,
		collision::constraint::type,
		sge::bullet::world &,
		unit radius,
		collision::solidity::type,
		collision::point const &position);
	
	collision::unit 
	radius() const;
	
	void 
	radius(
		collision::unit);
};
}
}
}

#endif