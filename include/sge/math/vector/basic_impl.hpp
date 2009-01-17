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


#ifndef SGE_MATH_VECTOR_BASIC_IMPL_HPP_INCLUDED
#define SGE_MATH_VECTOR_BASIC_IMPL_HPP_INCLUDED

#include "basic_decl.hpp"
#include "../detail/make_op_def.hpp"
#include "../detail/initial_size.hpp"

template<
	typename T,
	typename N,
	typename S
>
sge::math::vector::basic<T, N, S>::basic()
{}

#define SGE_MATH_VECTOR_BASIC_DEFINE_OPERATOR(op)\
SGE_MATH_DETAIL_MAKE_OP_DEF(basic, op)

SGE_MATH_VECTOR_BASIC_DEFINE_OPERATOR(+=)
SGE_MATH_VECTOR_BASIC_DEFINE_OPERATOR(-=)
SGE_MATH_VECTOR_BASIC_DEFINE_OPERATOR(*=)
SGE_MATH_VECTOR_BASIC_DEFINE_OPERATOR(/=)
SGE_MATH_VECTOR_BASIC_DEFINE_OPERATOR(%=)

#undef SGE_MATH_VECTOR_BASIC_DEFINE_OPERATOR

template<
	typename T,
	typename N,
	typename S
>
typename sge::math::vector::basic<T, N, S>::const_reference
sge::math::vector::basic<T, N, S>::operator[](
	size_type const index) const
{
	return storage[index];
}

template<
	typename T,
	typename N,
	typename S
>
typename sge::math::vector::basic<T, N, S>::reference
sge::math::vector::basic<T, N, S>::operator[](
	size_type const index)
{
	return storage[index];
}

template<
	typename T,
	typename N,
	typename S
>
void
sge::math::vector::basic<T, N, S>::resize(
	size_type const sz)
{
	storage.resize(
		sz);
}


template<
	typename T,
	typename N,
	typename S
>
void
sge::math::vector::basic<T, N, S>::initial_size(
	size_type const sz)
{
	::initial_size(
		storage,
		sz);
}


#endif
