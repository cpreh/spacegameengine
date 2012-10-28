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


#include <alda/net/buffer/max_send_size.hpp>
#include <alda/net/buffer/circular_send/boost_type.hpp>
#include <alda/net/buffer/circular_send/object.hpp>


alda::net::buffer::circular_send::object::object(
	alda::net::buffer::max_send_size const _buffer_max_size
)
:
	impl_(
		_buffer_max_size.get()
	)
{
}

alda::net::buffer::circular_send::object::~object()
{
}

alda::net::buffer::circular_send::boost_type::const_array_range const
alda::net::buffer::circular_send::object::send_part() const
{
	return
		impl_.array_two().second == 0u
		?
			impl_.array_one()
		:
			impl_.array_two();
}

void
alda::net::buffer::circular_send::object::erase_front(
	alda::net::buffer::circular_send::object::size_type const _size
)
{
	impl_.erase(
		impl_.begin(),
		impl_.begin()
		+
		static_cast<
			alda::net::buffer::circular_send::boost_type::iterator::difference_type
		>(
			_size
		)
	);
}

bool
alda::net::buffer::circular_send::object::empty() const
{
	return
		impl_.empty();
}

void
alda::net::buffer::circular_send::object::clear()
{
	impl_.clear();
}

alda::net::buffer::circular_send::object::size_type
alda::net::buffer::circular_send::object::space_left() const
{
	return
		impl_.capacity()
		-
		impl_.size();
}

alda::net::buffer::circular_send::boost_type &
alda::net::buffer::circular_send::object::get()
{
	return
		impl_;
}

alda::net::buffer::circular_send::boost_type const &
alda::net::buffer::circular_send::object::get() const
{
	return
		impl_;
}
