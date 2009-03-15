#ifndef SGE_SIGNAL_AUTO_CONNECTION_HPP_INCLUDED
#define SGE_SIGNAL_AUTO_CONNECTION_HPP_INCLUDED

#include <sge/signal/detail/connection.hpp>
#include <sge/auto_ptr.hpp>

namespace sge
{
namespace signal
{
typedef auto_ptr<detail::connection> auto_connection;
}
}

#endif
