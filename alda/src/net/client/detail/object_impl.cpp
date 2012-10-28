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
#include <alda/net/host.hpp>
#include <alda/net/io_service_wrapper.hpp>
#include <alda/net/log_location.hpp>
#include <alda/net/parameters.hpp>
#include <alda/net/port.hpp>
#include <alda/net/buffer/circular_receive/for_asio.hpp>
#include <alda/net/buffer/circular_receive/part.hpp>
#include <alda/net/buffer/circular_send/boost_type.hpp>
#include <alda/net/buffer/circular_send/object.hpp>
#include <alda/net/client/connect_callback.hpp>
#include <alda/net/client/data_callback.hpp>
#include <alda/net/client/error_callback.hpp>
#include <alda/src/log_parameters.hpp>
#include <alda/src/net/client/detail/object_impl.hpp>
#include <fcppt/from_std_string.hpp>
#include <fcppt/insert_to_std_string.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/ref.hpp>
#include <fcppt/string.hpp>
#include <fcppt/text.hpp>
#include <fcppt/assert/pre.hpp>
#include <fcppt/log/debug.hpp>
#include <fcppt/log/error.hpp>
#include <fcppt/log/location.hpp>
#include <fcppt/log/output.hpp>
#include <fcppt/log/verbose.hpp>
#include <fcppt/log/parameters/object.hpp>
#include <fcppt/signal/auto_connection.hpp>
#include <fcppt/signal/object_impl.hpp>
#include <fcppt/tr1/functional.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/asio/buffer.hpp>
#include <boost/asio/io_service.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/system/error_code.hpp>
#include <cstddef>
#include <fcppt/config/external_end.hpp>


namespace
{

fcppt::log::object logger(
	alda::log_parameters(
		alda::net::log_location()
		/
		FCPPT_TEXT("client")
	)
);

}

alda::net::client::detail::object_impl::object_impl(
	alda::net::parameters const &_parameters
)
:
	io_service_(
		_parameters.io_service_wrapper().get()
	),
	socket_(
		io_service_
	),
	resolver_(
		io_service_
	),
	query_(),
	receive_buffer_(
		_parameters.max_receive_size()
	),
	send_buffer_(
		_parameters.max_send_size()
	),
	connect_signal_(),
	error_signal_(),
	data_signal_(),
	sending_(
		false
	)
{
}

alda::net::client::detail::object_impl::~object_impl()
{
}

void
alda::net::client::detail::object_impl::connect(
	alda::net::host const &_host,
	alda::net::port const _port
)
{
	FCPPT_LOG_DEBUG(
		::logger,
		fcppt::log::_
			<< FCPPT_TEXT("resolving hostname ")
			<< fcppt::from_std_string(
				_host.get()
			)
			<< FCPPT_TEXT(" on port ")
			<< _port
	);

	query_.take(
		fcppt::make_unique_ptr<
			boost::asio::ip::tcp::resolver::query
		>(
			_host.get(),
			fcppt::insert_to_std_string(
				_port
			)
		)
	);

	resolver_.async_resolve(
		*query_,
		std::tr1::bind(
			&object_impl::resolve_handler,
			this,
			std::tr1::placeholders::_1,
			std::tr1::placeholders::_2
		)
	);
}

void
alda::net::client::detail::object_impl::disconnect()
{
	this->clear();
}

alda::net::buffer::circular_send::object &
alda::net::client::detail::object_impl::send_buffer()
{
	return send_buffer_;
}

void
alda::net::client::detail::object_impl::queue_send()
{
	if(
		!sending_
	)
		this->send_data();
}

fcppt::signal::auto_connection
alda::net::client::detail::object_impl::register_connect(
	alda::net::client::connect_callback const &_function
)
{
	return
		connect_signal_.connect(
			_function
		);
}

fcppt::signal::auto_connection
alda::net::client::detail::object_impl::register_error(
	alda::net::client::error_callback const &_function
)
{
	return
		error_signal_.connect(
			_function
		);
}

fcppt::signal::auto_connection
alda::net::client::detail::object_impl::register_data(
	alda::net::client::data_callback const &_function
)
{
	return
		data_signal_.connect(
			_function
		);
}

void
alda::net::client::detail::object_impl::resolve_handler(
	boost::system::error_code const &_error,
	boost::asio::ip::tcp::resolver::iterator _iterator
)
{
	if(
		_error
	)
	{
		this->handle_error(
			FCPPT_TEXT("resolving address: ")
			+
			fcppt::from_std_string(
				_error.message()
			),
			_error
		);

		return;
	}

	FCPPT_LOG_DEBUG(
		::logger,
		fcppt::log::_
			<< FCPPT_TEXT("resolved domain, trying to connect")
	);

	boost::asio::ip::tcp::endpoint const endpoint(
		*_iterator
	);

	socket_.async_connect(
		endpoint,
		std::tr1::bind(
			&object_impl::connect_handler,
			this,
			std::tr1::placeholders::_1,
			++_iterator
		)
	);
}

void
alda::net::client::detail::object_impl::handle_error(
	fcppt::string const &_message,
	boost::system::error_code const &_error
)
{
	this->clear();

	FCPPT_LOG_ERROR(
		::logger,
		fcppt::log::_
			<< _message
			<< FCPPT_TEXT(" (")
			<< fcppt::from_std_string(
				_error.message()
			)
			<< FCPPT_TEXT(')')
	);

	error_signal_(
		_message,
		_error
	);
}

void
alda::net::client::detail::object_impl::read_handler(
	boost::system::error_code const &_error,
	std::size_t const _bytes
)
{
	if(
		_error
	)
	{
		this->handle_error(
			FCPPT_TEXT("read"),
			_error
		);

		return;
	}

	receive_buffer_.bytes_received(
		_bytes
	);

	FCPPT_LOG_VERBOSE(
		::logger,
		fcppt::log::_
			<< FCPPT_TEXT("read ")
			<< _bytes
			<< FCPPT_TEXT(" bytes.")
	);

	data_signal_(
		fcppt::ref(
			receive_buffer_
		)
	);

	this->receive_data();
}

void
alda::net::client::detail::object_impl::write_handler(
	boost::system::error_code const &_error,
	std::size_t const _bytes
)
{
	if(
		_error
	)
	{
		this->handle_error(
			FCPPT_TEXT("write "),
			_error
		);

		return;
	}

	FCPPT_LOG_VERBOSE(
		::logger,
		fcppt::log::_
			<< FCPPT_TEXT("wrote ")
			<< _bytes
			<< FCPPT_TEXT(" bytes")
	);

	send_buffer_.erase_front(
		_bytes
	);

	if(
		!send_buffer_.empty()
	)
		this->send_data();
	else
		sending_ = false;
}

void
alda::net::client::detail::object_impl::connect_handler(
	boost::system::error_code const &_error,
	boost::asio::ip::tcp::resolver::iterator _iterator
)
{
	if(
		_error
	)
	{
		// are we at the end of the endpoint list?
		if(
			_iterator == boost::asio::ip::tcp::resolver::iterator()
			||
			_error == boost::asio::error::operation_aborted
		)
		{
			this->handle_error(
				FCPPT_TEXT("exhausted endpoints or connection aborted: ")+
				fcppt::from_std_string(
					_error.message()
				),
				_error
			);

			return;
		}

		FCPPT_LOG_DEBUG(
			::logger,
			fcppt::log::_
				<< FCPPT_TEXT("resolving next endpoint")
		);

		boost::asio::ip::tcp::endpoint const endpoint(
			*_iterator
		);

		socket_.async_connect(
			endpoint,
			std::tr1::bind(
				&object_impl::connect_handler,
				this,
				std::tr1::placeholders::_1,
				++_iterator
			)
		);

		return;
	}

	FCPPT_LOG_DEBUG(
		::logger,
		fcppt::log::_
			<< FCPPT_TEXT("connected")
	);

	connect_signal_();

	this->receive_data();
}

void
alda::net::client::detail::object_impl::send_data()
{
	alda::net::buffer::circular_send::boost_type::const_array_range const out_data(
		send_buffer_.send_part()
	);

	sending_ = (out_data.second != 0u);

	if(
		!sending_
	)
		return;

	socket_.async_send(
		boost::asio::buffer(
			out_data.first,
			out_data.second
		),
		std::tr1::bind(
			&alda::net::client::detail::object_impl::write_handler,
			this,
			std::tr1::placeholders::_1,
			std::tr1::placeholders::_2
		)
	);
}

void
alda::net::client::detail::object_impl::receive_data()
{
	FCPPT_ASSERT_PRE(
		!receive_buffer_.next_receive_part().empty()
	);

	socket_.async_receive(
		alda::net::buffer::circular_receive::for_asio(
			receive_buffer_
		),
		std::tr1::bind(
			&object_impl::read_handler,
			this,
			std::tr1::placeholders::_1,
			std::tr1::placeholders::_2
		)
	);
}

void
alda::net::client::detail::object_impl::clear()
{
	resolver_.cancel();

	query_.reset();

	socket_.close();

	send_buffer_.clear();

	receive_buffer_.clear();

	sending_ = false;
}
