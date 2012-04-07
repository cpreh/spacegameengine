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


#include <alda/net/buffer/circular_receive/for_asio.hpp>
#include <alda/net/buffer/circular_receive/object.hpp>
#include <alda/net/buffer/circular_receive/part.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/asio/buffer.hpp>
#include <algorithm>
#include <fcppt/config/external_end.hpp>


boost::asio::mutable_buffers_1 const
alda::net::buffer::circular_receive::for_asio(
	alda::net::buffer::circular_receive::object &_buffer
)
{
	alda::net::buffer::circular_receive::part const part(
		_buffer.next_receive_part()
	);

	return
		boost::asio::mutable_buffers_1(
			part.begin(),
			std::min(
				part.size(),
				static_cast<
					alda::net::buffer::circular_receive::object::size_type
				>(
					4096u
				)
			)
		);
}
