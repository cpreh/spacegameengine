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


#include <sge/renderer/matrix_pixel_to_space.hpp>
#include <fcppt/math/matrix/basic_impl.hpp>
#include <fcppt/math/matrix/translation.hpp>
#include <fcppt/math/matrix/scaling.hpp>
#include <fcppt/math/matrix/arithmetic.hpp>
#include <fcppt/math/dim/basic_impl.hpp>
#include <fcppt/math/instantiate_arithmetic.hpp>

template<
	typename T
>
typename sge::math::matrix::static_<T, 4, 4>::type const
sge::renderer::matrix_pixel_to_space(
	screen_size const &sz)
{
	return math::matrix::translation(
		static_cast<T>(-static_cast<int>(sz.w()) / 2),
		static_cast<T>(-static_cast<int>(sz.h()) / 2),
		static_cast<T>(0))
		* math::matrix::scaling(
			static_cast<T>(2) / static_cast<T>(sz.w()),
	        	static_cast<T>(-2) / static_cast<T>(sz.h()),
	        	static_cast<T>(1));
}

#define SGE_INSTANTIATE_MATRIX_PIXEL_TO_SPACE(x)\
template SGE_EXPORT_SYMBOL sge::math::matrix::static_<x, 4, 4>::type const \
sge::renderer::matrix_pixel_to_space<x>(\
	sge::renderer::screen_size const &);

SGE_MATH_INSTANTIATE_ARITHMETIC(SGE_INSTANTIATE_MATRIX_PIXEL_TO_SPACE)

#undef SGE_INSTANTIATE_MATRIX_PIXEL_TO_SPACE
