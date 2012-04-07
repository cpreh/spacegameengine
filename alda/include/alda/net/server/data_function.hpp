#ifndef ALDA_NET_SERVER_DATA_FUNCTION_HPP_INCLUDED
#define ALDA_NET_SERVER_DATA_FUNCTION_HPP_INCLUDED

#include <alda/net/id.hpp>
#include <alda/net/buffer/circular_receive/object_fwd.hpp>


namespace alda
{
namespace net
{
namespace server
{

typedef void
data_function(
	alda::net::id,
	alda::net::buffer::circular_receive::object &
);

}
}
}

#endif
