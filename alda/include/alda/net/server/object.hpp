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


#ifndef ALDA_NET_SERVER_OBJECT_HPP_INCLUDED
#define ALDA_NET_SERVER_OBJECT_HPP_INCLUDED

#include <alda/net/id.hpp>
#include <alda/net/io_service_wrapper_fwd.hpp>
#include <alda/net/port.hpp>
#include <alda/net/buffer/max_size.hpp>
#include <alda/net/buffer/circular_send/optional_ref_fwd.hpp>
#include <alda/net/server/connect_callback_fwd.hpp>
#include <alda/net/server/connection_id_container.hpp>
#include <alda/net/server/data_callback_fwd.hpp>
#include <alda/net/server/disconnect_callback_fwd.hpp>
#include <alda/net/server/detail/object_impl_fwd.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/scoped_ptr_impl.hpp>
#include <fcppt/signal/auto_connection_fwd.hpp>


namespace alda
{
namespace net
{
namespace server
{

class object
{
	FCPPT_NONCOPYABLE(
		object
	);
public:
	object(
		alda::net::io_service_wrapper const &,
		alda::net::buffer::max_size
	);

	~object();

	void
	listen(
		alda::net::port
	);

	alda::net::buffer::circular_send::optional_ref const
	send_buffer(
		alda::net::id
	);

	alda::net::server::connection_id_container const
	connections() const;

	void
	queue_send(
		alda::net::id
	);

	fcppt::signal::auto_connection
	register_connect(
		alda::net::server::connect_callback const &
	);

	fcppt::signal::auto_connection
	register_disconnect(
		alda::net::server::disconnect_callback const &
	);

	fcppt::signal::auto_connection
	register_data(
		alda::net::server::data_callback const &
	);

	void
	stop();
private:
	fcppt::scoped_ptr<
		alda::net::server::detail::object_impl
	> const impl_;
};

}
}
}

#endif
