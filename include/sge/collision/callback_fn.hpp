#ifndef SGE_COLLISION_CALLBACK_FN_HPP_INCLUDED
#define SGE_COLLISION_CALLBACK_FN_HPP_INCLUDED

#include <sge/collision/satellite_fwd.hpp>

namespace sge
{
namespace collision
{
typedef void callback_fn(satellite &,satellite &);
}
}

#endif