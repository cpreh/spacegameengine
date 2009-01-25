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


#ifndef SGE_MATH_DIM_IO_HPP_INCLUDED
#define SGE_MATH_DIM_IO_HPP_INCLUDED

#include "basic_decl.hpp"
#include "basic_impl.hpp"
#include <ostream>

namespace sge
{
namespace math
{
namespace dim
{

template<
	typename T,
	typename N,
	typename S,
	typename Ch,
	typename Traits
>
std::basic_ostream<Ch, Traits> &
operator<< (
	std::basic_ostream<Ch, Traits> &s,
	basic<T, N, S> const &v)
{
	s << s.widen('(');
	if(v.size() > 1)
		for(typename basic<T, N, S>::size_type i = 0; i < v.size() - 1; ++i)
			s << v[i] << s.widen(',');
	if(!v.empty())
		s << v.back();
	return s << s.widen(')');
}

}
}
}

#endif
