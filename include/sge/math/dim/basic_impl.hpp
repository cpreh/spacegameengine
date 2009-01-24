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


#ifndef SGE_MATH_DIM_BASIC_IMPL_HPP_INCLUDED
#define SGE_MATH_DIM_BASIC_IMPL_HPP_INCLUDED

#include "basic_decl.hpp"
#include "../detail/array_adapter_impl.hpp"
#include "../detail/make_op_def.hpp"
#include "../detail/storage_data.hpp"
#include "../detail/storage_dim.hpp"
#include "../detail/checked_access.hpp"
#include "../detail/make_variadic_constructor.hpp"
#include <numeric>
#include <functional>

template<
	typename T,
	typename N,
	typename S
>
sge::math::dim::basic<T, N, S>::basic()
{}

template<
	typename T,
	typename N,
	typename S
>
template<
	typename In
>
sge::math::dim::basic<T, N, S>::basic(
	In const beg,
	In const end)
{
}

#define SGE_MATH_DETAIL_MAKE_VARIADIC_CONSTRUCTOR_MAX_SIZE SGE_MATH_DIM_MAX_CTOR_PARAMS
#define SGE_MATH_TEMPLATE_PRE\
	template<\
		typename T,\
		typename N,\
		typename S\
	>
#define SGE_MATH_DEF_PRE\
	sge::math::dim::basic<T, N, S>

SGE_MATH_DETAIL_MAKE_VARIADIC_CONSTRUCTOR(
	SGE_MATH_TEMPLATE_PRE,
	SGE_MATH_DEF_PRE,
	basic)

#undef SGE_MATH_DEF_PRE
#undef SGE_MATH_TEMPLATE_PRE
#undef SGE_MATH_DETAIL_MAKE_VARIADIC_CONSTRUCTOR_MAX_SIZE

#define SGE_MATH_DIM_BASIC_DEFINE_OPERATOR(op)\
SGE_MATH_DETAIL_MAKE_OP_DEF(sge::math::dim::basic, op)

SGE_MATH_DIM_BASIC_DEFINE_OPERATOR(+=)
SGE_MATH_DIM_BASIC_DEFINE_OPERATOR(-=)
SGE_MATH_DIM_BASIC_DEFINE_OPERATOR(*=)
SGE_MATH_DIM_BASIC_DEFINE_OPERATOR(/=)
SGE_MATH_DIM_BASIC_DEFINE_OPERATOR(%=)

#undef SGE_MATH_DIM_BASIC_DEFINE_OPERATOR


template<
	typename T,
	typename N,
	typename S
>
typename sge::math::dim::basic<T, N, S>::reference
sge::math::dim::basic<T, N, S>::operator[](
	size_type const index)
{
	return storage[index];
}

template<
	typename T,
	typename N,
	typename S
>
typename sge::math::dim::basic<T, N, S>::const_reference
sge::math::dim::basic<T, N, S>::operator[](
	size_type const index) const
{
	return storage[index];
}

template<
	typename T,
	typename N,
	typename S
>
typename sge::math::dim::basic<T, N, S>::pointer
sge::math::dim::basic<T, N, S>::data()
{
	return math::detail::storage_data(
		storage);
}

template<
	typename T,
	typename N,
	typename S
>
typename sge::math::dim::basic<T, N, S>::const_pointer
sge::math::dim::basic<T, N, S>::data() const
{
	return math::detail::storage_data(
		storage);
}
	
template<
	typename T,
	typename N,
	typename S
>
typename sge::math::dim::basic<T, N, S>::size_type
sge::math::dim::basic<T, N, S>::size() const
{
	return static_cast<
		size_type
	>(
		math::detail::storage_dim(
			storage));
}
	
template<
	typename T,
	typename N,
	typename S
>
typename sge::math::dim::basic<T, N, S>::reference
sge::math::dim::basic<T, N, S>::w()
{
	return math::detail::checked_access<0>(*this);
}

template<
	typename T,
	typename N,
	typename S
>
typename sge::math::dim::basic<T, N, S>::const_reference
sge::math::dim::basic<T, N, S>::w() const
{
	return math::detail::checked_access<0>(*this);
}

template<
	typename T,
	typename N,
	typename S
>
typename sge::math::dim::basic<T, N, S>::reference
sge::math::dim::basic<T, N, S>::h()
{
	return math::detail::checked_access<1>(*this);
}

template<
	typename T,
	typename N,
	typename S
>
typename sge::math::dim::basic<T, N, S>::const_reference
sge::math::dim::basic<T, N, S>::h() const
{
	return math::detail::checked_access<1>(*this);
}

template<
	typename T,
	typename N,
	typename S
>
typename sge::math::dim::basic<T, N, S>::reference
sge::math::dim::basic<T, N, S>::d()
{
	return math::detail::checked_access<2>(*this);
}

template<
	typename T,
	typename N,
	typename S
>
typename sge::math::dim::basic<T, N, S>::const_reference
sge::math::dim::basic<T, N, S>::d() const
{
	return math::detail::checked_access<2>(*this);
}

template<
	typename T,
	typename N,
	typename S
>
typename sge::math::dim::basic<T, N, S>::size_type
sge::math::dim::basic<T, N, S>::content() const
{
	return std::accumulate(
		this->begin(),
		this->end(),
		1,
		std::multiplies<size_type>());
}

template<
	typename T,
	typename N,
	typename S
>
sge::math::dim::basic<T, N, S> const
sge::math::dim::basic<T, N, S>::null()
{
	basic ret;
	for(size_type i = 0; i < N::value; ++i)
		ret[i] = static_cast<value_type>(0);
	return ret;
}

#endif
