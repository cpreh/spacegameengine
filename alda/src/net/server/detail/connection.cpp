/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2012 Carl Philipp Reh (sefi@s-e-f-i.de)

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/


#include <alda/net/id.hpp>
#include <alda/net/buffer/max_receive_size.hpp>
#include <alda/net/buffer/max_send_size.hpp>
#include <alda/net/buffer/circular_receive/object.hpp>
#include <alda/net/buffer/circular_send/object.hpp>
#include <alda/src/net/server/detail/connection.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/asio/io_service.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <fcppt/config/external_end.hpp>


alda::net::server::detail::connection::connection(
	alda::net::id const _id,
	alda::net::buffer::max_receive_size const _buffer_receive_size,
	alda::net::buffer::max_send_size const _buffer_send_size,
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
		_buffer_send_size
	),
	received_data_(
		_buffer_receive_size
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
