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

#include "../types.hpp"
#include "./renderer_types.hpp"
#include "./texture.hpp"
#include "../math/types.hpp"

namespace sge
{

inline space_unit trans_x_2d_to_3d(const space_unit x)
{
	return x*2;
}

inline space_unit trans_y_2d_to_3d(const space_unit y)
{
	return -y*2;
}

inline pos3 trans_2d_to_3d(const point pos)
{
	return pos3(trans_x_2d_to_3d(pos.x), trans_y_2d_to_3d(pos.y), 0);
}

inline space_unit space_x_2d_to_3d(const space_unit x)
{
	return (x-0.5)*2;
}

inline space_unit space_y_2d_to_3d(const space_unit y)
{
	return (-y+0.5)*2;
}

inline pos3 space_2d_to_3d(const space_unit x, const space_unit y)
{
	return pos3(space_x_2d_to_3d(x),space_y_2d_to_3d(y),0);
}

inline pos3 space_2d_to_3d(const point pos)
{
	return space_2d_to_3d(pos.x,pos.y);
}

inline pos3 text_to_space(const space_unit x, const space_unit y)
{
	return space_2d_to_3d(x,y);
}

inline pos3 text_to_space(const point pos)
{
	return space_2d_to_3d(pos);
}

inline basic_vector2<unsigned> space_pos_to_pixel(const point a, const unsigned screen_width, const unsigned screen_height)
{
	return basic_vector2<unsigned>(unsigned((a.x + 1.0) / 2.0 * screen_width), unsigned((-a.y + 1.0) / 2.0 * screen_height));
}

inline unsigned space_size_to_pixel(const space_unit s, const unsigned screen_size)
{
	return unsigned((s / space_unit(2))) * screen_size;
}

inline space_unit pixel_size_to_space(const unsigned v, const unsigned screen_size)
{
	return space_unit(v * space_unit(2) / screen_size);
}

inline rect space_rect_2d_to_3d(const rect& r)
{
	return rect(space_x_2d_to_3d(r.left), space_y_2d_to_3d(r.top), space_x_2d_to_3d(r.right), space_y_2d_to_3d(r.bottom));
}

inline rect tex_size_to_space_rect(const lock_rect& l, const texture::size_type width, const texture::size_type height)
{
	return rect(space_unit(l.left+1) / width, space_unit(l.top+1) / height, space_unit(l.right-1) / width, space_unit(l.bottom-1) / height);
}

}

#endif
