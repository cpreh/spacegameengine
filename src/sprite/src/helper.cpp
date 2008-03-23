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
#include <boost/array.hpp>
#include <boost/foreach.hpp>
#include "../../renderer/transform.hpp"
#include "../../math/matrix_impl.hpp"
#include "../../math/rect_impl.hpp"
#include "../helper.hpp"

sge::vertex_buffer::iterator
	sge::fill_sprite_position(vertex_buffer::iterator it,
                                  const sprite_rect& rs,
                                  const sprite_depth_type z)
{
	const math::rect r = math::structure_cast<space_unit>(rs);

	(*it++).pos() = pos3(r.left(), r.top(), z);
	(*it++).pos() = pos3(r.right(), r.top(), z);
	(*it++).pos() = pos3(r.right(), r.bottom(), z);
	(*it++).pos() = pos3(r.left(), r.bottom(), z);

	return it;
}

sge::vertex_buffer::iterator
	sge::fill_sprite_tex_coordinates(vertex_buffer::iterator it,
                                         const tex_rect& rt)
{
	(*it++).tex() = tex_pos(rt.left(), rt.top());
	(*it++).tex() = tex_pos(rt.right(), rt.top());
	(*it++).tex() = tex_pos(rt.right(), rt.bottom());
	(*it++).tex() = tex_pos(rt.left(), rt.bottom());

	return it;
}

sge::vertex_buffer::iterator
	sge::fill_sprite_vertices(const vertex_buffer::iterator it,
                                  const sprite_rect& rs,
                                  const tex_rect& rt,
                                  const sprite_depth_type z)
{
	fill_sprite_position(it, rs, z);
	return fill_sprite_tex_coordinates(it, rt);
}

sge::vertex_buffer::iterator
	sge::fill_sprite_position_rotated(vertex_buffer::iterator it,
	                                  const sprite_rect& rbs,
                                          const sprite_rotation_type rot,
                                          const sprite_point& center,
                                          const sprite_depth_type z)
{
	const pos2 centerf(math::structure_cast<space_unit>(center));

	typedef boost::array<pos2, detail::vertices_per_sprite> position_array;
	const position_array positions = {
		{ pos2(static_cast<space_unit>(rbs.left()), static_cast<space_unit>(rbs.top())) - centerf,
		  pos2(static_cast<space_unit>(rbs.right()), static_cast<space_unit>(rbs.top())) - centerf,
		  pos2(static_cast<space_unit>(rbs.right()), static_cast<space_unit>(rbs.bottom())) - centerf,
		  pos2(static_cast<space_unit>(rbs.left()), static_cast<space_unit>(rbs.bottom())) - centerf
		}
	};

	const space_unit sinx = std::sin(rot),
	                 cosx = std::cos(rot);

	const math::basic_matrix<space_unit,2,2> mat_rot(cosx, -sinx,
	                                                 sinx,  cosx); 

	BOOST_FOREACH(position_array::const_reference p, positions)
		(*it++).pos() = pos3((mat_rot * p) + centerf, z);

	return it;
}

sge::vertex_buffer::iterator
	sge::fill_sprite_color(vertex_buffer::iterator it,
                               const color col)
{
	for(unsigned i = 0; i < detail::vertices_per_sprite; ++i)
		(*it++).diffuse() = col;
	return it;
}

sge::index_buffer::iterator
	sge::fill_sprite_indices(index_buffer::iterator it,
                                 const index_buffer::value_type start)
{
	(*it++) = start + 0;
	(*it++) = start + 1;
	(*it++) = start + 2;
	(*it++) = start + 0;
	(*it++) = start + 2;
	(*it++) = start + 3;

	return it;
}
