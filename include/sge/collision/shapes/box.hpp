#ifndef SGE_COLLISION_SHAPES_BOX_HPP_INCLUDED
#define SGE_COLLISION_SHAPES_BOX_HPP_INCLUDED

#include <sge/collision/shapes/base.hpp>
#include <sge/collision/shapes/box_fwd.hpp>
#include <sge/collision/dim.hpp>

namespace sge
{
namespace collision
{
namespace shapes
{
class box
:
	public base
{
public:
	virtual collision::dim const dim() const = 0;
	virtual void dim(
		collision::dim const &) = 0;
};
}
}
}

#endif
