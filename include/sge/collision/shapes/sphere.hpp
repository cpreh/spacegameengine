#ifndef SGE_COLLISION_SHAPES_SPHERE_HPP_INCLUDED
#define SGE_COLLISION_SHAPES_SPHERE_HPP_INCLUDED

#include <sge/collision/shapes/base.hpp>
#include <sge/collision/shapes/sphere_fwd.hpp>
#include <sge/collision/unit.hpp>

namespace sge
{
namespace collision
{
namespace shapes
{
class sphere
:
	public virtual base
{
public:
	virtual unit 
	radius() const = 0;
	
	virtual void 
	radius(
		unit) = 0;
};
}
}
}

#endif
