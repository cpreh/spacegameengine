#ifndef SGE_COLLISION_CALLBACK_HPP_INCLUDED
#define SGE_COLLISION_CALLBACK_HPP_INCLUDED

#include <sge/collision/callback_fn.hpp>
#include <sge/function/object_fwd.hpp>

namespace sge
{
namespace collision
{

typedef sge::function::object<
	callback_fn
> callback;

}
}

#endif
