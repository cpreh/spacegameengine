#ifndef ALDA_SRC_NET_SERVER_DETAIL_CONNECTION_HPP_INCLUDED
#define ALDA_SRC_NET_SERVER_DETAIL_CONNECTION_HPP_INCLUDED

#include <alda/net/id.hpp>
#include <alda/net/value_type.hpp>
#include <alda/net/buffer/max_size.hpp>
#include <alda/net/buffer/circular_send/object.hpp>
#include <alda/net/buffer/circular_receive/object.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/asio/io_service.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <fcppt/config/external_end.hpp>


namespace alda
{
namespace net
{
namespace server
{
namespace detail
{

class connection
{
	FCPPT_NONCOPYABLE(
		connection
	);
public:
	connection(
		alda::net::id,
		alda::net::buffer::max_size,
		boost::asio::io_service &
	);

	~connection();

	alda::net::id const
	id() const;

	boost::asio::ip::tcp::socket &
	socket();

	alda::net::buffer::circular_send::object &
	send_data();

	alda::net::buffer::circular_receive::object &
	received_data();

	bool &
	sending();
private:
	alda::net::id const id_;

	boost::asio::ip::tcp::socket socket_;

	alda::net::buffer::circular_send::object send_data_;

	alda::net::buffer::circular_receive::object received_data_;

	bool sending_;
};

}
}
}
}

#endif
