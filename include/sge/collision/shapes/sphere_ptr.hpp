#ifndef SGE_COLLISION_SHAPES_SPHERE_PTR_HPP_INCLUDED
#define SGE_COLLISION_SHAPES_SPHERE_PTR_HPP_INCLUDED

#include <sge/collision/shapes/sphere_fwd.hpp>
#include <fcppt/shared_ptr.hpp>

namespace sge
{
namespace collision
{
namespace shapes
{

typedef fcppt::shared_ptr<
	sphere
> sphere_ptr;

typedef fcppt::shared_ptr<
	sphere const
> const_sphere_ptr;

}
}
}

#endif
