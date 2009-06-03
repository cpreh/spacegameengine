/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2009 Carl Philipp Reh (sefi@s-e-f-i.de)

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



#include <sge/renderer/aspect.hpp>
#include <sge/math/dim/basic_impl.hpp>
#include <sge/math/instantiate_arithmetic.hpp>
#include <sge/math/almost_zero.hpp>
#include <sge/assert.hpp>

template<
	typename T
>
T
sge::renderer::aspect(
	screen_size const &sz)
{
	T const
		w(static_cast<T>(sz.w())),
		h(static_cast<T>(sz.h()));
	
	SGE_ASSERT(
		!math::almost_zero(w)
		&& !math::almost_zero(h)
	)
	
	return w > h
		? w / h
		: h / w;
}

#define SGE_INSTANTIATE_ASPECT(x)\
template SGE_SYMBOL x sge::renderer::aspect(sge::renderer::screen_size const &);

SGE_MATH_INSTANTIATE_ARITHMETIC(SGE_INSTANTIATE_ASPECT)

#undef SGE_INSTANTIATE_ASPECT
