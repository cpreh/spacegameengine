#ifndef SGE_COLLISION_SHAPES_SPHERE_PTR_HPP_INCLUDED
#define SGE_COLLISION_SHAPES_SPHERE_PTR_HPP_INCLUDED

#include <sge/collision/sphere_fwd.hpp>
#include <fcppt/shared_ptr.hpp>

namespace sge
{
namespace collision
{

typedef shared_ptr<
	sphere
> sphere_ptr;

typedef shared_ptr<
	sphere const
> const_sphere_ptr;

}
}

#endif
