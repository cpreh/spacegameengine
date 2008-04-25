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


#ifndef SGE_MATH_BASIC_SEQUENCE_IMPL_HPP_INCLUDED
#define SGE_MATH_BASIC_SEQUENCE_IMPL_HPP_INCLUDED

#include "basic_sequence.hpp"
#include <boost/foreach.hpp>

#define SGE_MATH_BINARY_OP_ASSIGN(x) \
template< \
	typename T, \
	sge::math::detail::dim_type Dim> \
sge::math::basic_sequence<T, Dim> & \
sge::math::basic_sequence<T, Dim>::operator x( \
	basic_sequence<T, Dim> const &r) \
{ \
	for(detail::dim_type i(0); i < Dim; ++i) \
		(*this)[i] x r[i]; \
	return *this; \
}

SGE_MATH_BINARY_OP_ASSIGN(+=)
SGE_MATH_BINARY_OP_ASSIGN(-=)
SGE_MATH_BINARY_OP_ASSIGN(*=)
SGE_MATH_BINARY_OP_ASSIGN(/=)
SGE_MATH_BINARY_OP_ASSIGN(%=)

#undef SGE_MATH_BINARY_OP_ASSIGN

#define SGE_MATH_UNARY_OP(x) \
template< \
	typename T, \
	sge::math::detail::dim_type Dim> \
sge::math::basic_sequence<T, Dim> \
sge::math::operator x( \
	basic_sequence<T, Dim> l) \
{ \
	for(unsigned i = 0; i < Dim; ++i) \
		l[i] = x l[i]; \
	return l; \
}

SGE_MATH_UNARY_OP(+)
SGE_MATH_UNARY_OP(-)

#undef SGE_MATH_UNARY_OP

#define SGE_MATH_BINARY_OP(x) \
template< \
	typename T, \
	sge::math::detail::dim_type Dim> \
sge::math::basic_sequence<T, Dim> \
sge::math::operator x( \
	basic_sequence<T, Dim> l, \
	basic_sequence<T, Dim> const &r) \
{ \
	return l x##= r; \
}

SGE_MATH_BINARY_OP(+)
SGE_MATH_BINARY_OP(-)
SGE_MATH_BINARY_OP(*)
SGE_MATH_BINARY_OP(/)
SGE_MATH_BINARY_OP(%)

#undef SGE_MATH_BINARY_OP

#define SGE_MATH_BINARY_OP_SCALAR(x) \
template< \
	typename T, \
	sge::math::detail::dim_type Dim> \
sge::math::basic_sequence<T, Dim> \
sge::math::operator x ( \
	basic_sequence<T, Dim> l, \
	typename basic_sequence<T, Dim>::const_reference r) \
{  \
	return l x##= r; \
}

SGE_MATH_BINARY_OP_SCALAR(+)
SGE_MATH_BINARY_OP_SCALAR(-)
SGE_MATH_BINARY_OP_SCALAR(/)
SGE_MATH_BINARY_OP_SCALAR(*)
SGE_MATH_BINARY_OP_SCALAR(%)

#define SGE_MATH_BINARY_OP_SCALAR_LEFT(x) \
template< \
	typename T, \
	sge::math::detail::dim_type Dim> \
sge::math::basic_sequence<T, Dim> \
sge::math::operator x ( \
	typename basic_sequence<T, Dim>::const_reference l, \
	basic_sequence<T, Dim> r) \
{ \
	return r x##= l; \
}

SGE_MATH_BINARY_OP_SCALAR_LEFT(+)
SGE_MATH_BINARY_OP_SCALAR_LEFT(-)
SGE_MATH_BINARY_OP_SCALAR_LEFT(*)

#undef SGE_MATH_BINARY_OP_SCALAR_LEFT

#endif
