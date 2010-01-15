#ifndef SGE_COLLISION_SHAPE_CALLBACK_HPP_INCLUDED
#define SGE_COLLISION_SHAPE_CALLBACK_HPP_INCLUDED

#include <sge/collision/shape_callback_fn.hpp>
#include <fcppt/function/object_fwd.hpp>

namespace sge
{
namespace collision
{

typedef fcppt::function::object
<
	shape_callback_fn
> shape_callback;

}
}

#endif
