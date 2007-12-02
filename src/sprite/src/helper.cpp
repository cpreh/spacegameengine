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


#include <cmath>
#include "../../renderer/transform.hpp"
#include "../../math/matrix.hpp"
#include "../../math/rect_impl.hpp"
#include "../helper.hpp"

sge::vertex_buffer::iterator sge::fill_sprite_position(vertex_buffer::iterator it, const math::rect& rs, const space_unit z)
{
	(*it++).pos() = pos3(rs.left(), rs.top(), z);
	(*it++).pos() = pos3(rs.right(), rs.top(), z);
	(*it++).pos() = pos3(rs.right(), rs.bottom(), z);
	(*it++).pos() = pos3(rs.left(), rs.bottom(), z);

	return it;
}

sge::vertex_buffer::iterator sge::fill_sprite_tex_coordinates(vertex_buffer::iterator it, const math::rect& rt)
{
	(*it++).tex() = tex_pos(rt.left(), rt.top());
	(*it++).tex() = tex_pos(rt.right(), rt.top());
	(*it++).tex() = tex_pos(rt.right(), rt.bottom());
	(*it++).tex() = tex_pos(rt.left(), rt.bottom());

	return it;
}

sge::vertex_buffer::iterator sge::fill_sprite_vertices(const vertex_buffer::iterator it, const math::rect& rs, const math::rect& rt, const space_unit z)
{
	fill_sprite_position(it, rs, z);
	return fill_sprite_tex_coordinates(it, rt);
}

sge::vertex_buffer::iterator sge::fill_sprite_position_rotated(vertex_buffer::iterator it, const math::rect& rbs, const space_unit rot, const math::vector2 center, const space_unit z)
{
	math::vector2 one = math::vector2(rbs.left(), rbs.top()) - center,
	              two = math::vector2(rbs.right(), rbs.top()) - center,
	              three = math::vector2(rbs.right(), rbs.bottom()) - center,
	              four = math::vector2(rbs.left(), rbs.bottom()) - center;

	const space_unit sinx = std::sin(-rot),
	                 cosx = std::cos(-rot);

	const math::basic_matrix<space_unit,2,2> mat_rot(cosx, -sinx,
	                                                 sinx,  cosx); 

	one = mat_rot * one;
	two = mat_rot * two;
	three = mat_rot * three;
	four = mat_rot * four;

	one += center;
	two += center;
	three += center;
	four += center;

	(*it++).pos() = pos3(one, z);
	(*it++).pos() = pos3(two, z);
	(*it++).pos() = pos3(three, z);
	(*it++).pos() = pos3(four, z);

	return it;
}

sge::vertex_buffer::iterator sge::fill_sprite_color(vertex_buffer::iterator it, const color col)
{
	for(unsigned i = 0; i < 4; ++i)
		(*it++).diffuse() = col;
	return it;
}

sge::index_buffer::iterator sge::fill_sprite_indices(index_buffer::iterator it, const index_buffer::value_type start)
{
	(*it++) = start + 0;
	(*it++) = start + 1;
	(*it++) = start + 2;
	(*it++) = start + 0;
	(*it++) = start + 2;
	(*it++) = start + 3;

	return it;
}
