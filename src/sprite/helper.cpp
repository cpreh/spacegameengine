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


#include <sge/sprite/helper.hpp>
#include <sge/renderer/transform.hpp>
#include <sge/math/matrix_impl.hpp>
#include <sge/math/rect_impl.hpp>
#include <boost/array.hpp>
#include <boost/foreach.hpp>
#include <cmath>

sge::renderer::vertex_buffer::iterator
sge::sprite::fill_position(
	renderer::vertex_buffer::iterator it,
	const rect& rs,
	const depth_type z)
{
	using renderer::pos3;
	const math::rect r = math::structure_cast<space_unit>(rs);

	(*it++).pos() = pos3(r.left(), r.top(), z);
	(*it++).pos() = pos3(r.right(), r.top(), z);
	(*it++).pos() = pos3(r.right(), r.bottom(), z);
	(*it++).pos() = pos3(r.left(), r.bottom(), z);

	return it;
}

sge::renderer::vertex_buffer::iterator
sge::sprite::fill_tex_coordinates(
	renderer::vertex_buffer::iterator it,
	const renderer::tex_rect& rt)
{
	using renderer::tex_pos;
	(*it++).tex() = tex_pos(rt.left(), rt.top());
	(*it++).tex() = tex_pos(rt.right(), rt.top());
	(*it++).tex() = tex_pos(rt.right(), rt.bottom());
	(*it++).tex() = tex_pos(rt.left(), rt.bottom());
	
	return it;
}

sge::renderer::vertex_buffer::iterator
sge::sprite::fill_vertices(
	const renderer::vertex_buffer::iterator it,
	const rect& rs,
	const renderer::tex_rect& rt,
	const depth_type z)
{
	fill_position(it, rs, z);
	return fill_tex_coordinates(it, rt);
}

sge::renderer::vertex_buffer::iterator
sge::sprite::fill_position_rotated(
	renderer::vertex_buffer::iterator it,
	const rect& rbs,
	const rotation_type rot,
	const point& center,
	const depth_type z)
{
	using renderer::pos2;
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

	const math::basic_matrix<space_unit,2,2> mat_rot(
		cosx, -sinx,
		sinx,  cosx); 

	BOOST_FOREACH(position_array::const_reference p, positions)
		(*it++).pos() = renderer::pos3((mat_rot * p) + centerf, z);

	return it;
}

sge::renderer::vertex_buffer::iterator
sge::sprite::fill_color(
	renderer::vertex_buffer::iterator it,
	const color col)
{
	for(unsigned i = 0; i < detail::vertices_per_sprite; ++i)
		(*it++).diffuse() = col[3] << 24 | col[2] << 16 | col[1] << 8 | col[0] ; // FIXME
	return it;
}

sge::sprite::index_view::iterator
sge::sprite::fill_indices(
	index_view::iterator it,
	const index_view::value_type start)
{
	(*it++) = static_cast<index_view::value_type>(start + 0);
	(*it++) = static_cast<index_view::value_type>(start + 1);
	(*it++) = static_cast<index_view::value_type>(start + 2);
	(*it++) = static_cast<index_view::value_type>(start + 0);
	(*it++) = static_cast<index_view::value_type>(start + 2);
	(*it++) = static_cast<index_view::value_type>(start + 3);

	return it;
}
