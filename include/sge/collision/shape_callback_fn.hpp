#ifndef SGE_COLLISION_SHAPE_CALLBACK_FN_HPP_INCLUDED
#define SGE_COLLISION_SHAPE_CALLBACK_FN_HPP_INCLUDED

#include <sge/collision/shapes/base_fwd.hpp>

namespace sge
{
namespace collision
{
typedef 
void shape_callback_fn(
	shapes::base_ptr,
	shapes::base_ptr);
}
}

#endif
