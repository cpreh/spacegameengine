#ifndef SGE_COLLISION_CALLBACKS_HPP_INCLUDED
#define SGE_COLLISION_CALLBACKS_HPP_INCLUDED

#include "sattelite_fwd.hpp"
#include <sge/signals/signal.hpp>
#include <boost/function.hpp>

namespace sge
{
namespace collision
{
typedef bool test_callback_fn(sattelite const &,sattelite const &);
typedef boost::function<test_callback_fn> test_callback;
typedef void callback_fn(sattelite &,sattelite &);
typedef boost::function<callback_fn> callback;
typedef sge::signals::signal<callback_fn> callback_signal;
}
}

#endif
