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


#define BOOST_ASIO_SOURCE

#include <boost/asio/detail/config.hpp>

#if defined(BOOST_ASIO_HEADER_ONLY)
# error Do not compile Asio library source with BOOST_ASIO_HEADER_ONLY defined
#endif

#include <boost/asio/impl/error.ipp>
#include <boost/asio/impl/io_service.ipp>
#include <boost/asio/impl/serial_port_base.ipp>
#include <boost/asio/detail/impl/descriptor_ops.ipp>
#include <boost/asio/detail/impl/dev_poll_reactor.ipp>
#include <boost/asio/detail/impl/epoll_reactor.ipp>
#include <boost/asio/detail/impl/eventfd_select_interrupter.ipp>
#include <boost/asio/detail/impl/kqueue_reactor.ipp>
#include <boost/asio/detail/impl/pipe_select_interrupter.ipp>
#include <boost/asio/detail/impl/posix_event.ipp>
#include <boost/asio/detail/impl/posix_mutex.ipp>
#include <boost/asio/detail/impl/posix_thread.ipp>
#include <boost/asio/detail/impl/posix_tss_ptr.ipp>
#include <boost/asio/detail/impl/reactive_descriptor_service.ipp>
#include <boost/asio/detail/impl/reactive_serial_port_service.ipp>
#include <boost/asio/detail/impl/reactive_socket_service_base.ipp>
#include <boost/asio/detail/impl/resolver_service_base.ipp>
#include <boost/asio/detail/impl/select_reactor.ipp>
#include <boost/asio/detail/impl/service_registry.ipp>
#include <boost/asio/detail/impl/socket_ops.ipp>
#include <boost/asio/detail/impl/socket_select_interrupter.ipp>
#include <boost/asio/detail/impl/strand_service.ipp>
#include <boost/asio/detail/impl/task_io_service.ipp>
#include <boost/asio/detail/impl/throw_error.ipp>
#include <boost/asio/detail/impl/timer_queue.ipp>
#include <boost/asio/detail/impl/timer_queue_set.ipp>
#include <boost/asio/detail/impl/win_iocp_handle_service.ipp>
#include <boost/asio/detail/impl/win_iocp_io_service.ipp>
#include <boost/asio/detail/impl/win_iocp_serial_port_service.ipp>
#include <boost/asio/detail/impl/win_iocp_socket_service_base.ipp>
#include <boost/asio/detail/impl/win_event.ipp>
#include <boost/asio/detail/impl/win_mutex.ipp>
#include <boost/asio/detail/impl/win_thread.ipp>
#include <boost/asio/detail/impl/win_tss_ptr.ipp>
#include <boost/asio/detail/impl/winsock_init.ipp>
#include <boost/asio/ip/impl/address.ipp>
#include <boost/asio/ip/impl/address_v4.ipp>
#include <boost/asio/ip/impl/address_v6.ipp>
#include <boost/asio/ip/impl/host_name.ipp>
#include <boost/asio/ip/detail/impl/endpoint.ipp>
#include <boost/asio/local/detail/impl/endpoint.ipp>
