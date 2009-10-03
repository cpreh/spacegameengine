#ifndef SGE_COLLISION_SHAPES_CIRCLE_HPP_INCLUDED
#define SGE_COLLISION_SHAPES_CIRCLE_HPP_INCLUDED

#include <sge/collision/shapes/base.hpp>
#include <sge/collision/shapes/circle_fwd.hpp>
#include <sge/collision/unit.hpp>

namespace sge
{
namespace collision
{
namespace shapes
{
class circle
:
	public base
{
public:
	virtual unit radius() const = 0;
	virtual void radius(
		unit) = 0;
};
}
}
}

#endif