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


#ifndef SGE_SPRITE_HELDER_HPP_INCLUDED
#define SGE_SPRITE_HELDER_HPP_INCLUDED

#include <cmath>
#include "../renderer/vertex_buffer.hpp"
#include "../renderer/index_buffer.hpp"
#include "../renderer/transform.hpp"
#include "../math/matrix2x2.hpp"
#include "../math/rect.hpp"

namespace sge
{

inline void fill_sprite_vertices(vertex_buffer::iterator& it, const rect& rsb, const rect& rt)
{
	const rect rs(space_rect_2d_to_3d(rsb));

	(*it  ).pos()    = pos3(rs.left,rs.top);
	(*it++).tex()[0] = tex_pos(rt.left,rt.top);

	(*it  ).pos()    = pos3(rs.right,rs.top);
	(*it++).tex()[0] = tex_pos(rt.right,rt.top);

	(*it  ).pos()    = pos3(rs.right,rs.bottom);
	(*it++).tex()[0] = tex_pos(rt.right,rt.bottom);

	(*it  ).pos()    = pos3(rs.left,rs.bottom);
	(*it++).tex()[0] = tex_pos(rt.left,rt.bottom);
}

inline void fill_sprite_vertices_rotated(vertex_buffer::iterator& it, const rect& rbs, const space_unit rot, const point center, const rect& rt)
{
	point one = point(rbs.left,rbs.top) - center,
	      two = point(rbs.right,rbs.top) - center,
	      three = point(rbs.right,rbs.bottom) - center,
	      four = point(rbs.left,rbs.bottom) - center;

	const space_unit sinx = std::sin(rot),
	                 cosx = std::cos(rot);

	const matrix2x2<space_unit> mat_rot(cosx, -sinx,
	                                    sinx,  cosx);

	one = mat_rot * one;
	two = mat_rot * two;
	three = mat_rot * three;
	four = mat_rot * four;

	one += center;
	two += center;
	three += center;
	four += center;

	(*it  ).pos()    = space_2d_to_3d(one);
	(*it++).tex()[0] = tex_pos(rt.left, rt.top);

	(*it  ).pos()    = space_2d_to_3d(two);
	(*it++).tex()[0] = tex_pos(rt.right, rt.top);

	(*it  ).pos()    = space_2d_to_3d(three);
	(*it++).tex()[0] = tex_pos(rt.right, rt.bottom);

	(*it  ).pos()    = space_2d_to_3d(four);
	(*it++).tex()[0] = tex_pos(rt.left, rt.bottom);
}

inline void fill_sprite_indices(index_buffer::iterator& it, const index_buffer::value_type start)
{
	(*it++) = start + 0;
	(*it++) = start + 1;
	(*it++) = start + 2;
	(*it++) = start + 0;
	(*it++) = start + 2;
	(*it++) = start + 3;
}

}

#endif
