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


#include <alda/net/exception.hpp>
#include <alda/net/id.hpp>
#include <alda/net/io_service_wrapper.hpp>
#include <alda/net/log_location.hpp>
#include <alda/net/parameters.hpp>
#include <alda/net/port.hpp>
#include <alda/net/buffer/circular_receive/for_asio.hpp>
#include <alda/net/buffer/circular_receive/part.hpp>
#include <alda/net/buffer/circular_send/boost_type.hpp>
#include <alda/net/buffer/circular_send/object.hpp>
#include <alda/net/buffer/circular_send/optional_ref.hpp>
#include <alda/net/server/connect_callback.hpp>
#include <alda/net/server/connection_id_container.hpp>
#include <alda/net/server/data_callback.hpp>
#include <alda/net/server/disconnect_callback.hpp>
#include <alda/net/server/detail/connection_container.hpp>
#include <alda/src/net/server/detail/connection.hpp>
#include <alda/src/net/server/detail/object_impl.hpp>
#include <alda/src/log_parameters.hpp>
#include <fcppt/assert/pre.hpp>
#include <fcppt/container/ptr/insert_unique_ptr_map.hpp>
#include <fcppt/tr1/functional.hpp>
#include <fcppt/log/debug.hpp>
#include <fcppt/log/error.hpp>
#include <fcppt/log/location.hpp>
#include <fcppt/log/object.hpp>
#include <fcppt/log/output.hpp>
#include <fcppt/log/verbose.hpp>
#include <fcppt/log/parameters/object.hpp>
#include <fcppt/from_std_string.hpp>
#include <fcppt/ref.hpp>
#include <fcppt/text.hpp>
#include <fcppt/signal/auto_connection.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/asio/buffer.hpp>
#include <boost/asio/io_service.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/range/adaptor/map.hpp>
#include <boost/system/error_code.hpp>
#include <cstddef>
#include <fcppt/config/external_end.hpp>


namespace
{

fcppt::log::object logger(
	alda::log_parameters(
		alda::net::log_location()
		/
		FCPPT_TEXT("server")
	)
);

}


alda::net::server::detail::object_impl::object_impl(
	alda::net::parameters const &_parameters
)
:
	io_service_(
		_parameters.io_service_wrapper().get()
	),
	buffer_receive_size_(
		_parameters.max_receive_size()
	),
	buffer_send_size_(
		_parameters.max_send_size()
	),
	acceptor_(
		io_service_
	),
	id_counter_(
		0u
	),
	new_connection_(),
	connections_(),
	connect_signal_(),
	disconnect_signal_(),
	data_signal_()
{
}

alda::net::server::detail::object_impl::~object_impl()
{
}

void
alda::net::server::detail::object_impl::listen(
	alda::net::port const _port
)
{
	FCPPT_LOG_DEBUG(
		::logger,
		fcppt::log::_
			<< FCPPT_TEXT("listening on port ")
			<< _port
	);

	boost::asio::ip::tcp::endpoint const endpoint(
		boost::asio::ip::tcp::v4(),
		static_cast<
			unsigned short
		>(
			_port.get()
		)
	);

	acceptor_.open(
		endpoint.protocol()
	);

	acceptor_.set_option(
		boost::asio::ip::tcp::acceptor::reuse_address(
			true
		)
	);

	acceptor_.bind(
		endpoint
	);

	acceptor_.listen();

	this->accept();
}

alda::net::buffer::circular_send::optional_ref const
alda::net::server::detail::object_impl::send_buffer(
	alda::net::id const _id
)
{
	alda::net::server::detail::connection_container::iterator const it(
		connections_.find(
			_id
		)
	);

	return
		it == connections_.end()
		?
			alda::net::buffer::circular_send::optional_ref()
		:
			alda::net::buffer::circular_send::optional_ref(
				it->second->send_data()
			);
}

alda::net::server::connection_id_container const
alda::net::server::detail::object_impl::connections() const
{
	return
		boost::adaptors::keys(
			connections_
		);
}

void
alda::net::server::detail::object_impl::queue_send(
	alda::net::id const _id
)
{
	alda::net::server::detail::connection_container::iterator const it(
		connections_.find(
			_id
		)
	);

	FCPPT_ASSERT_PRE(
		it != connections_.end()
	);

	alda::net::server::detail::connection &con(
		*it->second
	);

	if(
		!con.sending()
	)
		this->send_data(
			con
		);
}

fcppt::signal::auto_connection
alda::net::server::detail::object_impl::register_connect(
	alda::net::server::connect_callback const &_callback
)
{
	return
		connect_signal_.connect(
			_callback
		);
}

fcppt::signal::auto_connection
alda::net::server::detail::object_impl::register_disconnect(
	alda::net::server::disconnect_callback const &_callback
)
{
	return
		disconnect_signal_.connect(
			_callback
		);
}

fcppt::signal::auto_connection
alda::net::server::detail::object_impl::register_data(
	alda::net::server::data_callback const &_callback
)
{
	return
		data_signal_.connect(
			_callback
		);
}

void
alda::net::server::detail::object_impl::accept()
{
	new_connection_ =
		fcppt::make_unique_ptr<
			alda::net::server::detail::connection
		>(
			alda::net::id(
				id_counter_++
			),
			buffer_receive_size_,
			buffer_send_size_,
			fcppt::ref(
				io_service_
			)
		);

	acceptor_.async_accept(
		new_connection_->socket(),
		std::tr1::bind(
			&object_impl::accept_handler,
			this,
			std::tr1::placeholders::_1
		)
	);
}

void
alda::net::server::detail::object_impl::read_handler(
	boost::system::error_code const &_error,
	std::size_t const _bytes,
	alda::net::server::detail::connection &_con
)
{
	if(
		_error
	)
	{
		this->handle_error(
			FCPPT_TEXT("server read"),
			_error,
			_con
		);

		return;
	}

	FCPPT_LOG_VERBOSE(
		::logger,
		fcppt::log::_
			<< FCPPT_TEXT("reading ")
			<< _bytes
			<< FCPPT_TEXT(" bytes.")
	);

	_con.received_data().bytes_received(
		_bytes
	);

	data_signal_(
		_con.id(),
		fcppt::ref(
			_con.received_data()
		)
	);

	this->receive_data(
		_con
	);
}

void
alda::net::server::detail::object_impl::write_handler(
	boost::system::error_code const &_error,
	std::size_t const _bytes,
	alda::net::server::detail::connection &_con
)
{
	if(
		_error
	)
	{
		this->handle_error(
			FCPPT_TEXT("write"),
			_error,
			_con
		);

		return;
	}

	FCPPT_LOG_VERBOSE(
		::logger,
		fcppt::log::_
			<< FCPPT_TEXT("wrote ")
			<< _bytes
			<< FCPPT_TEXT(" bytes.")
	);

	alda::net::buffer::circular_send::object &sent_data(
		_con.send_data()
	);

	sent_data.erase_front(
		_bytes
	);

	if(
		!sent_data.empty()
	)
		this->send_data(
			_con
		);
	else
		_con.sending() = false;
}

void
alda::net::server::detail::object_impl::accept_handler(
	boost::system::error_code const &_error
)
{
	if(
		_error
	)
	{
		FCPPT_LOG_DEBUG(
			::logger,
			fcppt::log::_
				<< FCPPT_TEXT("error while accepting")
		);

		this->accept();

		return;
	}

	FCPPT_LOG_DEBUG(
		::logger,
		fcppt::log::_
			<< FCPPT_TEXT("accepting a connection, id is ")
			<< new_connection_->id()
	);

	FCPPT_ASSERT_PRE(
		new_connection_
	);

	alda::net::server::detail::connection &current_con(
		*new_connection_
	);

	if(
		!fcppt::container::ptr::insert_unique_ptr_map(
			connections_,
			current_con.id(),
			move(
				new_connection_
			)
		).second
	)
		throw net::exception(
			FCPPT_TEXT("Double insert in net::server!")
		);

	// send signal to handlers
	connect_signal_(
		current_con.id()
	);

	this->receive_data(
		current_con
	);

	this->accept();
}

void
alda::net::server::detail::object_impl::handle_error(
	fcppt::string const &_message,
	boost::system::error_code const &_error,
	alda::net::server::detail::connection const &_con
)
{
	fcppt::string const error_msg(
		_message
		+ FCPPT_TEXT(": ")
		+
		fcppt::from_std_string(
			_error.message()
		)
	);

	FCPPT_LOG_DEBUG(
		::logger,
		fcppt::log::_
			<< FCPPT_TEXT("disconnected ")
			<< _con.id()
			<< FCPPT_TEXT(" (")
			<< error_msg
			<< FCPPT_TEXT(")")
	);

	net::id const id(
		_con.id()
	);

	// remove the connection first, so really nothing will be sent anymore
	if(
		!connections_.erase(
			id
		)
	)
		throw net::exception(
			FCPPT_TEXT("Invalid erase in net::server!")
		);

	disconnect_signal_(
		id,
		error_msg
	);
}

void
alda::net::server::detail::object_impl::send_data(
	alda::net::server::detail::connection &_con
)
{
	alda::net::buffer::circular_send::boost_type::const_array_range const out_data(
		_con.send_data().send_part()
	);

	_con.sending() = (out_data.second != 0u);

	if(
		!_con.sending()
	)
		return;

	_con.socket().async_send(
		boost::asio::buffer(
			out_data.first,
			out_data.second
		),
		std::tr1::bind(
			&object_impl::write_handler,
			this,
			std::tr1::placeholders::_1,
			std::tr1::placeholders::_2,
			fcppt::ref(
				_con
			)
		)
	);
}

void
alda::net::server::detail::object_impl::receive_data(
	alda::net::server::detail::connection &_con
)
{
	FCPPT_ASSERT_PRE(
		!_con.received_data().next_receive_part().empty()
	);

	// receive some more
	_con.socket().async_receive(
		alda::net::buffer::circular_receive::for_asio(
			_con.received_data()
		),
		std::tr1::bind(
			&object_impl::read_handler,
			this,
			std::tr1::placeholders::_1,
			std::tr1::placeholders::_2,
			fcppt::ref(
				_con
			)
		)
	);
}
