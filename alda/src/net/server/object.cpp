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
#include <alda/net/parameters_fwd.hpp>
#include <alda/net/port.hpp>
#include <alda/net/buffer/circular_send/optional_ref.hpp>
#include <alda/net/server/connect_callback_fwd.hpp>
#include <alda/net/server/connection_id_container.hpp>
#include <alda/net/server/data_callback_fwd.hpp>
#include <alda/net/server/disconnect_callback_fwd.hpp>
#include <alda/net/server/object.hpp>
#include <alda/src/net/server/detail/object_impl.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/cref.hpp>
#include <fcppt/signal/auto_connection.hpp>


alda::net::server::object::object(
	alda::net::parameters const &_parameters
)
:
	impl_(
		fcppt::make_unique_ptr<
			alda::net::server::detail::object_impl
		>(
			fcppt::cref(
				_parameters
			)
		)
	)
{
}

alda::net::server::object::~object()
{
}

void
alda::net::server::object::listen(
	alda::net::port const _port
)
{
	return
		impl_->listen(
			_port
		);
}

alda::net::buffer::circular_send::optional_ref const
alda::net::server::object::send_buffer(
	alda::net::id const _id
)
{
	return
		impl_->send_buffer(
			_id
		);
}

alda::net::server::connection_id_container const
alda::net::server::object::connections() const
{
	return
		impl_->connections();
}

void
alda::net::server::object::queue_send(
	alda::net::id const _id
)
{
	return
		impl_->queue_send(
			_id
		);
}

fcppt::signal::auto_connection
alda::net::server::object::register_connect(
	alda::net::server::connect_callback const &_callback
)
{
	return
		impl_->register_connect(
			_callback
		);
}

fcppt::signal::auto_connection
alda::net::server::object::register_disconnect(
	alda::net::server::disconnect_callback const &_callback
)
{
	return
		impl_->register_disconnect(
			_callback
		);
}

fcppt::signal::auto_connection
alda::net::server::object::register_data(
	alda::net::server::data_callback const &_callback
)
{
	return
		impl_->register_data(
			_callback
		);
}
