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


#include <alda/net/host.hpp>
#include <alda/net/parameters_fwd.hpp>
#include <alda/net/port.hpp>
#include <alda/net/buffer/circular_send/object_fwd.hpp>
#include <alda/net/client/connect_callback_fwd.hpp>
#include <alda/net/client/data_callback_fwd.hpp>
#include <alda/net/client/error_callback_fwd.hpp>
#include <alda/net/client/object.hpp>
#include <alda/src/net/client/detail/object_impl.hpp>
#include <fcppt/cref.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/signal/auto_connection.hpp>


alda::net::client::object::object(
	alda::net::parameters const &_parameters
)
:
	impl_(
		fcppt::make_unique_ptr<
			alda::net::client::detail::object_impl
		>(
			fcppt::cref(
				_parameters
			)
		)
	)
{
}

alda::net::client::object::~object()
{
}

void
alda::net::client::object::connect(
	alda::net::host const &_host,
	alda::net::port const _port
)
{
	return
		impl_->connect(
			_host,
			_port
		);
}

void
alda::net::client::object::disconnect()
{
	return impl_->disconnect();
}

alda::net::buffer::circular_send::object &
alda::net::client::object::send_buffer()
{
	return
		impl_->send_buffer();
}

void
alda::net::client::object::queue_send()
{
	impl_->queue_send();
}

fcppt::signal::auto_connection
alda::net::client::object::register_connect(
	alda::net::client::connect_callback const &_callback
)
{
	return
		impl_->register_connect(
			_callback
		);
}

fcppt::signal::auto_connection
alda::net::client::object::register_error(
	alda::net::client::error_callback const &_callback
)
{
	return
		impl_->register_error(
			_callback
		);
}

fcppt::signal::auto_connection
alda::net::client::object::register_data(
	alda::net::client::data_callback const &_callback
)
{
	return
		impl_->register_data(
			_callback
		);
}
