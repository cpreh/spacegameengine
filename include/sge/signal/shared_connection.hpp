#ifndef SGE_SIGNAL_SHARED_CONNECTION_HPP_INCLUDED
#define SGE_SIGNAL_SHARED_CONNECTION_HPP_INCLUDED

#include <sge/signal/detail/connection_fwd.hpp>
#include <sge/shared_ptr.hpp>

namespace sge
{
namespace signal
{
typedef shared_ptr<detail::connection> shared_connection;
}
}

#endif
