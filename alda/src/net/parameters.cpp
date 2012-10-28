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


#include <alda/net/io_service_wrapper_fwd.hpp>
#include <alda/net/parameters.hpp>
#include <alda/net/buffer/max_receive_size.hpp>
#include <alda/net/buffer/max_send_size.hpp>


alda::net::parameters::parameters(
	alda::net::io_service_wrapper const &_io_service_wrapper,
	alda::net::buffer::max_send_size const _max_send_size,
	alda::net::buffer::max_receive_size const _max_receive_size
)
:
	io_service_wrapper_(
		_io_service_wrapper
	),
	max_send_size_(
		_max_send_size
	),
	max_receive_size_(
		_max_receive_size
	)
{
}

alda::net::io_service_wrapper const &
alda::net::parameters::io_service_wrapper() const
{
	return io_service_wrapper_;
}

alda::net::buffer::max_send_size const
alda::net::parameters::max_send_size() const
{
	return max_send_size_;
}

alda::net::buffer::max_receive_size const
alda::net::parameters::max_receive_size() const
{
	return max_receive_size_;
}
