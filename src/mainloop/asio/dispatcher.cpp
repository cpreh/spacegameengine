/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2010 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include <sge/mainloop/asio/dispatcher.hpp>
#include <fcppt/tr1/functional.hpp>
#include <boost/asio/buffer.hpp>

sge::mainloop::asio::dispatcher::dispatcher(	
	boost::asio::io_service &_io_service,
	mainloop::native_handle const _handle,
	mainloop::dispatcher_callback const &_callback
)
:
	stream_wrapper_(
		_io_service,
		_handle
	),
	callback_(
		_callback
	)
{
	register_handler();
}

sge::mainloop::asio::dispatcher::~dispatcher()
{}

void
sge::mainloop::asio::dispatcher::register_handler()
{
	stream_wrapper_.async_read_some(
		boost::asio::null_buffers(),
		std::tr1::bind(
			&dispatcher::callback,
			this,
			std::tr1::placeholders::_1
		)
	);
}

void
sge::mainloop::asio::dispatcher::callback(
	boost::system::error_code const &_error
)
{
	if(
		_error
	)
		return;

	callback_();

	register_handler();
}
