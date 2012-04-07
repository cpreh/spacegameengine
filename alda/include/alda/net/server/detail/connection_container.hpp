#ifndef ALDA_NET_SERVER_DETAIL_CONNECTION_CONTAINER_HPP_INCLUDED
#define ALDA_NET_SERVER_DETAIL_CONNECTION_CONTAINER_HPP_INCLUDED

#include <alda/net/id.hpp>
#include <alda/net/server/detail/connection_fwd.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/ptr_container/ptr_map.hpp>
#include <fcppt/config/external_end.hpp>


namespace alda
{
namespace net
{
namespace server
{
namespace detail
{

typedef boost::ptr_map<
	alda::net::id,
	alda::net::server::detail::connection
> connection_container;

}
}
}
}

#endif
