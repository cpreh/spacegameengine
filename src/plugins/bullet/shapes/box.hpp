#ifndef SGE_BULLET_SHAPES_BOX_HPP_INCLUDED
#define SGE_BULLET_SHAPES_BOX_HPP_INCLUDED

#include "base.hpp"
#include "../box.hpp"
#include "../world_fwd.hpp"
#include <sge/collision/shapes/box.hpp>
#include <BulletCollision/CollisionShapes/btBoxShape.h>

namespace sge
{
namespace bullet
{
namespace shapes
{
class box
:
	public base,
	public collision::shapes::box
{
public:
	box(
		collision::satellite_ptr,
		collision::constraint::type,
		sge::bullet::world &,
		collision::point const &position,
		collision::solidity::type,
		collision::dim const &);
	
	collision::dim const 
	dim() const;
	
	void 
	dim(
		collision::dim const &);
};
}
}
}

#endif