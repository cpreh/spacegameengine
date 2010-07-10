/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2009 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include <sge/mainloop/asio_io_service.hpp>

sge::mainloop::asio_io_service::asio_io_service()
:
	io_service_()
{}

sge::mainloop::asio_io_service::~asio_io_service()
{
}

void
sge::mainloop::asio_io_service::run_one()
{
	io_service_.run_one();
}

void
sge::mainloop::asio_io_service::run()
{
	io_service_.run();
}

void
sge::mainloop::asio_io_service::poll()
{
	io_service_.poll();
}

void
sge::mainloop::asio_io_service::stop()
{
	io_service_.stop();
}

void
sge::mainloop::asio_io_service::reset()
{
	io_service_.reset();
}
