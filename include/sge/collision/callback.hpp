#ifndef SGE_COLLISION_CALLBACK_HPP_INCLUDED
#define SGE_COLLISION_CALLBACK_HPP_INCLUDED

#include <sge/collision/callback_fn.hpp>
#include <boost/function.hpp>

namespace sge
{
namespace collision
{
typedef boost::function<callback_fn> callback;
}
}

#endif