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


#ifndef SGE_MATH_MATRIX_BASIC_IMPL_HPP_INCLUDED
#define SGE_MATH_MATRIX_BASIC_IMPL_HPP_INCLUDED

#include "basic_decl.hpp"
#include "../compare.hpp"
#include "../vector/basic_impl.hpp"
#include "../detail/array_adapter_impl.hpp"
#include "../detail/storage_data.hpp"
#include "../detail/view_storage_impl.hpp"
#include "../detail/make_variadic_constructor.hpp"
#include <algorithm>

template<
	typename T,
	typename N,
	typename M,
	typename S
>
sge::math::matrix::basic<T, N, M, S>::basic()
{}

template<
	typename T,
	typename N,
	typename M,
	typename S
>
template<
	typename In
>
sge::math::matrix::basic<T, N, M, S>::basic(
	In const beg,
	In const end)
{
	std::copy(
		beg,
		end,
		data());
}

template<
	typename T,
	typename N,
	typename M,
	typename S
>
typename sge::math::matrix::basic<T, N, M, S>::reference
sge::math::matrix::basic<T, N, M, S>::operator[](
	size_type const j)
{
	return reference(
		typename reference::storage_type(
			data() + j * N::value,
			M::value));
}

template<
	typename T,
	typename N,
	typename M,
	typename S
>
typename sge::math::matrix::basic<T, N, M, S>::const_reference const
sge::math::matrix::basic<T, N, M, S>::operator[](
	size_type const j) const
{
	return const_reference(
		typename const_reference::storage_type(
			data() + j * N::value,
			M::value));
}

template<
	typename T,
	typename N,
	typename M,
	typename S
>
typename sge::math::matrix::basic<T, N, M, S>::pointer
sge::math::matrix::basic<T, N, M, S>::data()
{
	return math::detail::storage_data(
		storage);
}

template<
	typename T,
	typename N,
	typename M,
	typename S
>
typename sge::math::matrix::basic<T, N, M, S>::const_pointer
sge::math::matrix::basic<T, N, M, S>::data() const
{
	return const_cast<
		basic &
	>(
		*this).data();
}

template<
	typename T,
	typename N,
	typename M,
	typename S
>
typename sge::math::matrix::basic<T, N, M, S>::size_type
sge::math::matrix::basic<T, N, M, S>::size() const
{
	return storage_dim(
		storage);
}

#endif
