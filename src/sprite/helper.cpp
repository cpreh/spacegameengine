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
#include <sge/renderer/color_convert.hpp>
#include <sge/renderer/vf/vertex.hpp>
#include <sge/math/matrix_impl.hpp>
#include <sge/math/rect_impl.hpp>
#include <boost/array.hpp>
#include <boost/foreach.hpp>
#include <cmath>

sge::sprite::vertex_iterator
sge::sprite::fill_position(
	vertex_iterator it,
	rect const &rs,
	depth_type const z)
{
	math::rect const r = math::structure_cast<space_unit>(rs);

/*	(*it++).set<vertex_pos>(pos3(r.left(), r.top(), z));
	(*it++).set<vertex_pos>(pos3(r.right(), r.top(), z));
	(*it++).set<vertex_pos>(pos3(r.right(), r.bottom(), z));
	(*it++).set<vertex_pos>(pos3(r.left(), r.bottom(), z));
*/
	return it;
}

sge::sprite::vertex_iterator
sge::sprite::fill_tex_coordinates(
	vertex_iterator it,
	tex_rect const &rt)
{
/*	(*it++).set<vertex_texpos>(tex_pos(rt.left(), rt.top()));
	(*it++).set<vertex_texpos>(tex_pos(rt.right(), rt.top()));
	(*it++).set<vertex_texpos>(tex_pos(rt.right(), rt.bottom()));
	(*it++).set<vertex_texpos>(tex_pos(rt.left(), rt.bottom()));
	*/
	return it;
}

sge::sprite::vertex_iterator
sge::sprite::fill_vertices(
	vertex_iterator const it,
	rect const &rs,
	tex_rect const &rt,
	depth_type const z)
{
	fill_position(it, rs, z);
	return fill_tex_coordinates(it, rt);
}

sge::sprite::vertex_iterator
sge::sprite::fill_position_rotated(
	vertex_iterator it,
	rect const &rbs,
	rotation_type const rot,
	point const &center,
	depth_type const z)
{
	pos2 const centerf(
		math::structure_cast<space_unit>(center));

	typedef boost::array<pos2, detail::vertices_per_sprite> position_array;
	position_array const positions = {{
		pos2(
			static_cast<space_unit>(rbs.left()),
			static_cast<space_unit>(rbs.top())) - centerf,
		pos2(
			static_cast<space_unit>(rbs.right()),
			static_cast<space_unit>(rbs.top())) - centerf,
		pos2(
			static_cast<space_unit>(rbs.right()),
			static_cast<space_unit>(rbs.bottom())) - centerf,
		pos2(
			static_cast<space_unit>(rbs.left()),
			static_cast<space_unit>(rbs.bottom())) - centerf
	}};

	space_unit const sinx = std::sin(rot),
	                 cosx = std::cos(rot);

	math::basic_matrix<space_unit,2,2> const mat_rot(
		cosx, -sinx,
		sinx,  cosx); 

//	BOOST_FOREACH(position_array::const_reference p, positions)
//		(*it++).set<vertex_pos>(pos3((mat_rot * p) + centerf, z));

	return it;
}

sge::sprite::vertex_iterator
sge::sprite::fill_color(
	vertex_iterator it,
	color const acol)
{
	renderer::rgba8_color const col(
		renderer::color_convert<renderer::rgba8_color>(
			acol));
	
//	for(unsigned i = 0; i < detail::vertices_per_sprite; ++i)
//		(*it++).set<vertex_color>(col);
	return it;
}

sge::sprite::index_view::iterator
sge::sprite::fill_indices(
	index_view::iterator it,
	index_view::value_type const start)
{
	(*it++) = static_cast<index_view::value_type>(start + 0);
	(*it++) = static_cast<index_view::value_type>(start + 1);
	(*it++) = static_cast<index_view::value_type>(start + 2);
	(*it++) = static_cast<index_view::value_type>(start + 0);
	(*it++) = static_cast<index_view::value_type>(start + 2);
	(*it++) = static_cast<index_view::value_type>(start + 3);

	return it;
}
