#include <alda/net/id.hpp>
#include <alda/net/buffer/max_size.hpp>
#include <alda/net/buffer/circular_receive/object.hpp>
#include <alda/net/buffer/circular_send/object.hpp>
#include <alda/src/net/server/detail/connection.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/asio/io_service.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <fcppt/config/external_end.hpp>


alda::net::server::detail::connection::connection(
	alda::net::id const _id,
	alda::net::buffer::max_size const _buffer_max_size,
	boost::asio::io_service &_io_service
)
:
	id_(
		_id
	),
	socket_(
		_io_service
	),
	send_data_(
		_buffer_max_size
	),
	received_data_(
		_buffer_max_size
	),
	sending_(
		false
	)
{
}

alda::net::server::detail::connection::~connection()
{
}

alda::net::id const
alda::net::server::detail::connection::id() const
{
	return id_;
}

boost::asio::ip::tcp::socket &
alda::net::server::detail::connection::socket()
{
	return socket_;
}

alda::net::buffer::circular_send::object &
alda::net::server::detail::connection::send_data()
{
	return send_data_;
}

alda::net::buffer::circular_receive::object &
alda::net::server::detail::connection::received_data()
{
	return received_data_;
}

bool &
alda::net::server::detail::connection::sending()
{
	return sending_;
}
