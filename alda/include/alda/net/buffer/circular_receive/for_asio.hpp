#ifndef ALDA_NET_BUFFER_CIRCULAR_RECEIVE_FOR_ASIO_HPP_INCLUDED
#define ALDA_NET_BUFFER_CIRCULAR_RECEIVE_FOR_ASIO_HPP_INCLUDED

#include <alda/net/buffer/circular_receive/object_fwd.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/asio/buffer.hpp>
#include <fcppt/config/external_end.hpp>


namespace alda
{
namespace net
{
namespace buffer
{
namespace circular_receive
{

boost::asio::mutable_buffers_1 const
for_asio(
	alda::net::buffer::circular_receive::object &
);

}
}
}
}

#endif
