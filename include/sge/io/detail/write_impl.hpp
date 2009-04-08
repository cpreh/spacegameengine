/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2007  Carl Philipp Reh (sefi@s-e-f-i.de)

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


#ifndef SGE_IO_DETAIL_WRITE_IMPL_HPP_INCLUDED
#define SGE_IO_DETAIL_WRITE_IMPL_HPP_INCLUDED

#include <sge/endianness/from_host.hpp>
#include <ostream>

template<
	typename T
>
typename boost::enable_if<boost::is_fundamental<T>, void>::type
sge::io::write(
	std::ostream &s,
	T const &t,
	endianness::format::type const fmt)
{
	T const tmp(
		endianness::from_host(
			t,
			fmt
		)
	);

	s.write(
		reinterpret_cast<char const *>(&tmp),
		sizeof(T)
	);
}

#endif
