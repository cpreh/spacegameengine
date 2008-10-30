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


#ifndef SGE_RENDERER_MATRIX_PIXEL_TO_SPACE_HPP_INCLUDED
#define SGE_RENDERER_MATRIX_PIXEL_TO_SPACE_HPP_INCLUDED

#include "screen_types.hpp"
#include "../math/matrix.hpp"
#include "../math/matrix_impl.hpp"
#include "../math/matrix_util.hpp"

namespace sge
{
namespace renderer
{

template<
	typename T
>
math::basic_matrix<T, 4, 4> const
matrix_pixel_to_space(
	screen_size_t const &sz)
{
	return math::matrix_translation(
		static_cast<T>(-static_cast<int>(sz.w()) / 2),
		static_cast<T>(-static_cast<int>(sz.h()) / 2),
		static_cast<T>(0))
		* math::matrix_scaling(
			static_cast<T>(2) / static_cast<T>(sz.w()),
	        	static_cast<T>(-2) / static_cast<T>(sz.h()),
	        	static_cast<T>(1));
}

}
}

#endif
