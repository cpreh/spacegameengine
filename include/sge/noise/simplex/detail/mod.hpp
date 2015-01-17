/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2015 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#ifndef SGE_NOISE_SIMPLEX_DETAIL_MOD_HPP_INCLUDED
#define SGE_NOISE_SIMPLEX_DETAIL_MOD_HPP_INCLUDED

#include <fcppt/config/external_begin.hpp>
#include <cstddef>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace noise
{
namespace simplex
{
namespace detail
{

inline
std::size_t
mod(
	long const &a,
	std::size_t const &b)
{
	if (a >= 0)
		return static_cast<std::size_t>(a) %
			static_cast<std::size_t>(b);
	else
		return static_cast<std::size_t>(-a) %
			static_cast<std::size_t>(b);
}

}
}
}
}

#endif

