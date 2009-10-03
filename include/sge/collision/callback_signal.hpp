#ifndef SGE_COLLISION_CALLBACK_SIGNAL_HPP_INCLUDED
#define SGE_COLLISION_CALLBACK_SIGNAL_HPP_INCLUDED

#include <sge/signal/object.hpp>
#include <sge/collision/callback_fn.hpp>

namespace sge
{
namespace collision
{
typedef sge::signal::object<callback_fn> callback_signal;
}
}

#endif