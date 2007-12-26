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


#include "../../su.hpp"
#include "../../math/rect_impl.hpp"
#include "../transform.hpp"

sge::math::space_matrix sge::matrix_pixel_to_space(const screen_size_t& sz)
{
	return math::matrix_translation(static_cast<space_unit>(-static_cast<int>(sz.w()) / 2),
	                                static_cast<space_unit>(-static_cast<int>(sz.h()) / 2),
	                                0)
	     * math::matrix_scaling(su(2) / static_cast<space_unit>(sz.w()),
	                            su(-2) / static_cast<space_unit>(sz.h()),
	                            0);
}

sge::math::rect sge::tex_size_to_space_rect(const lock_rect& l,
                                            const texture::dim_type& dim,
                                            const space_unit repeat)
{
	return math::rect(static_cast<space_unit>(l.left()) / static_cast<space_unit>(dim.w()),
	                  static_cast<space_unit>(l.top()) / static_cast<space_unit>(dim.h()),
	                  repeat * static_cast<space_unit>(l.right()) / static_cast<space_unit>(dim.w()),
	                  repeat * static_cast<space_unit>(l.bottom()) / static_cast<space_unit>(dim.h()));
}
