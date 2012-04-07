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


#include <alda/net/buffer/circular_receive/part.hpp>
#include <fcppt/config/external_begin.hpp>
#include <iterator>
#include <fcppt/config/external_end.hpp>


alda::net::buffer::circular_receive::part::part(
	pointer const _begin,
	pointer const _end
)
:
	begin_(
		_begin
	),
	end_(
		_end
	)
{
}

alda::net::buffer::circular_receive::part::pointer
alda::net::buffer::circular_receive::part::begin() const
{
	return begin_;
}

alda::net::buffer::circular_receive::part::pointer
alda::net::buffer::circular_receive::part::end() const
{
	return end_;
}

alda::net::buffer::circular_receive::part::size_type
alda::net::buffer::circular_receive::part::size() const
{
	return
		static_cast<
			alda::net::buffer::circular_receive::part::size_type
		>(
			std::distance(
				this->begin(),
				this->end()
			)
		);
}

bool
alda::net::buffer::circular_receive::part::empty() const
{
	return
		this->size() == 0u;
}
