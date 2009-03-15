#ifndef SGE_SIGNAL_SCOPED_CONNECTION_HPP_INCLUDED
#define SGE_SIGNAL_SCOPED_CONNECTION_HPP_INCLUDED

#include <sge/signal/detail/connection_fwd.hpp>
#include <sge/scoped_ptr.hpp>

namespace sge
{
namespace signal
{
typedef scoped_ptr<detail::connection> scoped_connection;
}
}

#endif
