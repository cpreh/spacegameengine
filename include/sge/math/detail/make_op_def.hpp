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


#ifndef SGE_MATH_DETAILMAKE_OP_DEF_HPP_INCLUDED
#define SGE_MATH_DETAILMAKE_OP_DEF_HPP_INCLUDED

#include "storage_dim.hpp"

#define SGE_MATH_DETAIL_MAKE_OP_DEF(name, op)\
template< \
	typename T, \
	typename N, \
	typename S \
> \
template< \
	typename Expr \
> \
name< \
	T, \
	N, \
	S \
> & \
name< \
	T, \
	N, \
	S \
>::operator op ( \
	Expr const &expr) \
{ \
	size_type const dim(\
		static_cast<\
			size_type\
		>( \
			::sge::math::detail::storage_dim(\
				storage)));\
	for( \
		size_type i = 0; \
		i < dim; \
		++i \
	) \
		(*this)[i] op expr[i]; \
	return *this; \
}

#endif
