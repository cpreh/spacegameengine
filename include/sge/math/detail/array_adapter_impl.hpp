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


#ifndef SGE_MATH_DETAIL_ARRAY_ADAPTER_IMPL_HPP_INCLUDED
#define SGE_MATH_DETAIL_ARRAY_ADAPTER_IMPL_HPP_INCLUDED

#include "array_adapter.hpp"
#include <sge/math/compare.hpp>
#include <sge/assert.hpp>
#include <functional>
#include <algorithm>

template<
	typename Derived,
	typename ValueType,
	typename SizeType,
	typename Reference,
	typename ConstReference
>
Reference
sge::math::detail::array_adapter<
	Derived,
	ValueType,
	SizeType,
	Reference,
	ConstReference
>::at(
	size_type const index)
{
	SGE_ASSERT(index < this_().size());
	return this_()[index];
}

template<
	typename Derived,
	typename ValueType,
	typename SizeType,
	typename Reference,
	typename ConstReference
>
ConstReference
sge::math::detail::array_adapter<
	Derived,
	ValueType,
	SizeType,
	Reference,
	ConstReference
>::at(
	size_type const index) const
{
	SGE_ASSERT(index < this_().size());
	return this_()[index];
}

template<
	typename Derived,
	typename ValueType,
	typename SizeType,
	typename Reference,
	typename ConstReference
>
typename
sge::math::detail::array_adapter<
	Derived,
	ValueType,
	SizeType,
	Reference,
	ConstReference
>::pointer
sge::math::detail::array_adapter<
	Derived,
	ValueType,
	SizeType,
	Reference,
	ConstReference
>::data_end()
{
	return this_().data() + this_().size();
}

template<
	typename Derived,
	typename ValueType,
	typename SizeType,
	typename Reference,
	typename ConstReference
>
typename
sge::math::detail::array_adapter<
	Derived,
	ValueType,
	SizeType,
	Reference,
	ConstReference
>::const_pointer
sge::math::detail::array_adapter<
	Derived,
	ValueType,
	SizeType,
	Reference,
	ConstReference
>::data_end() const
{
	return this_().data() + this_().size();
}

template<
	typename Derived,
	typename ValueType,
	typename SizeType,
	typename Reference,
	typename ConstReference
>
typename
sge::math::detail::array_adapter<
	Derived,
	ValueType,
	SizeType,
	Reference,
	ConstReference
>::iterator
sge::math::detail::array_adapter<
	Derived
	,ValueType,
	SizeType,
	Reference,
	ConstReference
>::begin()
{
	return iterator(
		this_().data());
}

template<
	typename Derived,
	typename ValueType,
	typename SizeType,
	typename Reference,
	typename ConstReference
>
typename
sge::math::detail::array_adapter<
	Derived,
	ValueType,
	SizeType,
	Reference,
	ConstReference
>::const_iterator
sge::math::detail::array_adapter<
	Derived,
	ValueType,
	SizeType,
	Reference,
	ConstReference
>::begin() const
{
	return const_iterator(
		this_().data());
}

template<
	typename Derived,
	typename ValueType,
	typename SizeType,
	typename Reference,
	typename ConstReference
>
typename
sge::math::detail::array_adapter<
	Derived,
	ValueType,
	SizeType,
	Reference,
	ConstReference
>::iterator
sge::math::detail::array_adapter<
	Derived,
	ValueType,
	SizeType,
	Reference,
	ConstReference
>::end()
{
	return iterator(
		data_end());
}

template<
	typename Derived,
	typename ValueType,
	typename SizeType,
	typename Reference,
	typename ConstReference
>
typename
sge::math::detail::array_adapter<
	Derived,
	ValueType,
	SizeType,
	Reference,
	ConstReference
>::const_iterator
sge::math::detail::array_adapter<
	Derived,
	ValueType,
	SizeType,
	Reference,
	ConstReference
>::end() const
{
	return const_iterator(
		data_end());
}

template<
	typename Derived,
	typename ValueType,
	typename SizeType,
	typename Reference,
	typename ConstReference
>
typename
sge::math::detail::array_adapter<
	Derived,
	ValueType,
	SizeType,
	Reference,
	ConstReference
>::reverse_iterator
sge::math::detail::array_adapter<
	Derived,
	ValueType,
	SizeType,
	Reference,
	ConstReference
>::rbegin()
{
	return reverse_iterator(
		end());
}

template<
	typename Derived,
	typename ValueType,
	typename SizeType,
	typename Reference,
	typename ConstReference
>
typename
sge::math::detail::array_adapter<
	Derived,
	ValueType,
	SizeType,
	Reference,
	ConstReference
>::const_reverse_iterator
sge::math::detail::array_adapter<
	Derived,
	ValueType,
	SizeType,
	Reference,
	ConstReference
>::rbegin() const
{
	return const_reverse_iterator(
		end());
}

template<
	typename Derived,
	typename ValueType,
	typename SizeType,
	typename Reference,
	typename ConstReference
>
typename
sge::math::detail::array_adapter<
	Derived,
	ValueType,
	SizeType,
	Reference,
	ConstReference
>::reverse_iterator
sge::math::detail::array_adapter<
	Derived,
	ValueType,
	SizeType,
	Reference,
	ConstReference
>::rend()
{
	return reverse_iterator(
		begin());
}

template<
	typename Derived,
	typename ValueType,
	typename SizeType,
	typename Reference,
	typename ConstReference
>
typename
sge::math::detail::array_adapter<
	Derived,
	ValueType,
	SizeType,
	Reference,
	ConstReference
>::const_reverse_iterator
sge::math::detail::array_adapter<
	Derived,
	ValueType,
	SizeType,
	Reference,
	ConstReference
>::rend() const
{
	return const_reverse_iterator(
		begin());
}

template<
	typename Derived,
	typename ValueType,
	typename SizeType,
	typename Reference,
	typename ConstReference
>
bool
sge::math::detail::array_adapter<
	Derived,
	ValueType,
	SizeType,
	Reference,
	ConstReference
>::empty() const
{
	return !this_().size();
}

template<
	typename Derived,
	typename ValueType,
	typename SizeType,
	typename Reference,
	typename ConstReference
>
bool
sge::math::detail::array_adapter<
	Derived,
	ValueType,
	SizeType,
	Reference,
	ConstReference
>::operator==(
	Derived const &r) const
{
	return this_().size() == r.size()
		&& std::equal(
			begin(),
			end(),
			r.begin(),
			std::ptr_fun(
				compare<
					ValueType	
				>));
}

template<
	typename Derived,
	typename ValueType,
	typename SizeType,
	typename Reference,
	typename ConstReference
>
bool
sge::math::detail::array_adapter<
	Derived,
	ValueType,
	SizeType,
	Reference,
	ConstReference
>::operator!=(
	Derived const &r) const
{
	return *this != r;
}

template<
	typename Derived,
	typename ValueType,
	typename SizeType,
	typename Reference,
	typename ConstReference
>
Derived &
sge::math::detail::array_adapter<
	Derived,
	ValueType,
	SizeType,
	Reference,
	ConstReference
>::this_()
{
	return static_cast<Derived &>(*this);
}

template<
	typename Derived,
	typename ValueType,
	typename SizeType,
	typename Reference,
	typename ConstReference
>
Derived const &
sge::math::detail::array_adapter<
	Derived,
	ValueType,
	SizeType,
	Reference,
	ConstReference
>::this_() const
{
	return static_cast<Derived const &>(*this);
}

#endif
