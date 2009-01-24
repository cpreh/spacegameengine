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

template<
	typename T,
	typename N,
	typename S
>
sge::math::dim::basic<T, N, S>::basic()
{}

#if 0
	template<
		typename In
	>
	basic(
		In beg,
		In end);

	reference
	operator[](
		size_type);

	const_reference
	operator[](
		size_type) const;
	
	pointer data();
	const_pointer data() const;
	
	size_type size() const;
	
	reference w();
	const_reference w() const;
	reference h();
	const_reference h() const;
	reference d();
	const_reference d() const;

	size_type content() const;
//	{
//		return std::accumulate(begin(), end(), 1, std::multiplies<size_type>());
//	}

	static basic const
	null();

#endif

#endif
