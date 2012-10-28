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


#ifndef ALDA_SRC_NET_CLIENT_DETAIL_OBJECT_IMPL_HPP_INCLUDED
#define ALDA_SRC_NET_CLIENT_DETAIL_OBJECT_IMPL_HPP_INCLUDED

#include <alda/net/parameters_fwd.hpp>
#include <alda/net/port.hpp>
#include <alda/net/host.hpp>
#include <alda/net/buffer/circular_receive/object.hpp>
#include <alda/net/buffer/circular_send/object.hpp>
#include <alda/net/client/connect_callback_fwd.hpp>
#include <alda/net/client/connect_function.hpp>
#include <alda/net/client/data_callback_fwd.hpp>
#include <alda/net/client/data_function.hpp>
#include <alda/net/client/error_callback_fwd.hpp>
#include <alda/net/client/error_function.hpp>
#include <alda/net/client/detail/object_impl_fwd.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/scoped_ptr_impl.hpp>
#include <fcppt/string.hpp>
#include <fcppt/signal/auto_connection_fwd.hpp>
#include <fcppt/signal/object_decl.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/asio/io_service.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/system/error_code.hpp>
#include <cstddef>
#include <fcppt/config/external_end.hpp>


namespace alda
{
namespace net
{
namespace client
{
namespace detail
{

class object_impl
{
	FCPPT_NONCOPYABLE(
		object_impl
	);
public:
	explicit
	object_impl(
		alda::net::parameters const &
	);

	~object_impl();

	void
	connect(
		alda::net::host const &,
		alda::net::port
	);

	void
	disconnect();

	alda::net::buffer::circular_send::object &
	send_buffer();

	void
	queue_send();

	fcppt::signal::auto_connection
	register_connect(
		alda::net::client::connect_callback const &
	);

	fcppt::signal::auto_connection
	register_error(
		alda::net::client::error_callback const &
	);

	fcppt::signal::auto_connection
	register_data(
		alda::net::client::data_callback const &
	);
private:
	boost::asio::io_service &io_service_;

	boost::asio::ip::tcp::socket socket_;

	boost::asio::ip::tcp::resolver resolver_;

	fcppt::scoped_ptr<
		boost::asio::ip::tcp::resolver::query
	> query_;

	alda::net::buffer::circular_receive::object receive_buffer_;

	alda::net::buffer::circular_send::object send_buffer_;

	fcppt::signal::object<
		alda::net::client::connect_function
	> connect_signal_;

	fcppt::signal::object<
		alda::net::client::error_function
	> error_signal_;

	fcppt::signal::object<
		alda::net::client::data_function
	> data_signal_;

	bool sending_;

	void
	handle_error(
		fcppt::string const &,
		boost::system::error_code const &
	);

	void
	read_handler(
		boost::system::error_code const &,
		std::size_t
	);

	void
	write_handler(
		boost::system::error_code const &,
		std::size_t
	);

	void
	resolve_handler(
		boost::system::error_code const &,
		boost::asio::ip::tcp::resolver::iterator
	);

	void
	connect_handler(
		boost::system::error_code const &,
		boost::asio::ip::tcp::resolver::iterator
	);

	void
	send_data();

	void
	receive_data();

	void
	clear();
};

}
}
}
}

#endif
