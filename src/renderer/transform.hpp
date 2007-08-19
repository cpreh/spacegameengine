/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006  Carl Philipp Reh (sefi@s-e-f-i.de)

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
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

inline math::space_matrix matrix_2d_to_3d()
{
	return math::matrix_translation(-0.5,-0.5,0) * math::matrix_scaling(2,-2,0);
}

inline space_unit trans_x_2d_to_3d(const space_unit x)
{
	return x*2;
}

inline space_unit trans_y_2d_to_3d(const space_unit y)
{
	return -y*2;
}

inline pos3 trans_2d_to_3d(const math::vector2 pos)
{
	return pos3(trans_x_2d_to_3d(pos.x()), trans_y_2d_to_3d(pos.y()), 0);
}

inline space_unit space_x_2d_to_3d(const space_unit x)
{
	return (x - space_unit(0.5))*2;
}

inline space_unit space_y_2d_to_3d(const space_unit y)
{
	return (-y + space_unit(0.5))*2;
}

inline pos3 space_2d_to_3d(const space_unit x, const space_unit y)
{
	return pos3(space_x_2d_to_3d(x),space_y_2d_to_3d(y),0);
}

inline pos3 space_2d_to_3d(const math::vector2 pos)
{
	return space_2d_to_3d(pos.x(), pos.y());
}

inline pos3 text_to_space(const space_unit x, const space_unit y)
{
	return space_2d_to_3d(x,y);
}

inline pos3 text_to_space(const math::vector2 pos)
{
	return space_2d_to_3d(pos);
}

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

inline space_unit pixel_size_to_space(const pixel_unit v, const screen_unit screen_size)
{
	return static_cast<space_unit>(v * space_unit(2) / screen_size);
}

template<typename Ret>
inline Ret pixel_pos_to_2d(const pixel_pos_t pos, const screen_size_t screen_sz)
{
	assert(screen_sz.w() && screen_sz.h());
	return Ret(static_cast<space_unit>(pos.x()) / screen_sz.w(),
	           static_cast<space_unit>(pos.y()) / screen_sz.h());
}

inline math::rect space_rect_2d_to_3d(const math::rect& r)
{
	return math::rect(space_x_2d_to_3d(r.left), space_y_2d_to_3d(r.top), space_x_2d_to_3d(r.right), space_y_2d_to_3d(r.bottom));
}

inline math::rect tex_size_to_space_rect(const lock_rect& l, const texture::size_type width, const texture::size_type height, const space_unit repeat = 1)
{
	return math::rect(static_cast<space_unit>(l.left) / width,
	                  static_cast<space_unit>(l.top) / height,
	                  repeat * static_cast<space_unit>(l.right) / width,
	                  repeat * static_cast<space_unit>(l.bottom) / height);
}

}

#endif
