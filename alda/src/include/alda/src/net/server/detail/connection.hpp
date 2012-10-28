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


#ifndef ALDA_SRC_NET_SERVER_DETAIL_CONNECTION_HPP_INCLUDED
#define ALDA_SRC_NET_SERVER_DETAIL_CONNECTION_HPP_INCLUDED

#include <alda/net/id.hpp>
#include <alda/net/value_type.hpp>
#include <alda/net/buffer/max_receive_size.hpp>
#include <alda/net/buffer/max_send_size.hpp>
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
		alda::net::buffer::max_receive_size,
		alda::net::buffer::max_send_size,
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
