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


#ifndef SGE_MATH_VECTOR_IMPL_HPP_INCLUDED
#define SGE_MATH_VECTOR_IMPL_HPP_INCLUDED

#include "vector.hpp"

template<
	typename T>
typename sge::math::detail::vector_policy<T, 1>::reference
sge::math::detail::vector_policy<T, 1>::x()
{
	return data_[0];
}

template<
	typename T>
typename sge::math::detail::vector_policy<T, 1>::const_reference
sge::math::detail::vector_policy<T, 1>::x() const
{
	return const_cast<vector_policy<T, 1>&>
		(*this).x();
}

/*template<
	typename T,
	sge::math::detail::dim_type Dim>
typename sge::math::detail::vector_policy<T, Dim>::reference
sge::math::detail::vector_policy<T, Dim>::x()
{
	return data_[0];
}

template<
	typename T,
	sge::math::detail::dim_type Dim>
sge::math::detail::vector_policy<T, Dim>::vector_policy(
	const pointer data_)
: data_(data_)
{}*/

#endif
