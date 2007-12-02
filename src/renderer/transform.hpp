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


#ifndef SGE_TRANSFORM_HPP_INCLUDED
#define SGE_TRANSFORM_HPP_INCLUDED

#include <cassert>
#include "types.hpp"
#include "texture.hpp"
#include "../math/rect.hpp"
#include "../math/matrix.hpp"

namespace sge
{

math::space_matrix matrix_2d_to_3d();

space_unit trans_x_2d_to_3d(space_unit x);

space_unit trans_y_2d_to_3d(space_unit y);

pos3 trans_2d_to_3d(math::vector2 pos);

space_unit space_x_2d_to_3d(space_unit x);

space_unit space_y_2d_to_3d(space_unit y);

pos3 space_2d_to_3d(space_unit x, space_unit y);

pos3 space_2d_to_3d(math::vector2 pos);

pos3 text_to_space(space_unit x, space_unit y);

pos3 text_to_space(math::vector2 pos);

template<typename Ret>
inline Ret space_size_to_pixel(const space_unit s, const screen_unit screen_size)
{
	return static_cast<Ret>(s * screen_size);
}

template<typename Ret, typename T>
inline Ret space_size_to_pixel(const T t, const screen_size_t screen_sz)
{
	typedef typename Ret::value_type value_type;
	return Ret(space_size_to_pixel<value_type>(t.at(0), screen_sz.w()),
	           space_size_to_pixel<value_type>(t.at(1), screen_sz.h()));
}

space_unit pixel_size_to_space(pixel_unit v, screen_unit screen_size);

template<typename Ret>
inline Ret pixel_pos_to_2d(const pixel_pos_t pos, const screen_size_t screen_sz)
{
	assert(screen_sz.w() && screen_sz.h());
	return Ret(static_cast<space_unit>(pos.x()) / screen_sz.w(),
	           static_cast<space_unit>(pos.y()) / screen_sz.h());
}

math::rect space_rect_2d_to_3d(const math::rect& r);
math::rect tex_size_to_space_rect(const lock_rect& l, texture::size_type width, texture::size_type height, space_unit repeat = 1);

}

#endif
