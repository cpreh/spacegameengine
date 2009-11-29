/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2009 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include <sge/sprite/detail/helper.hpp>
#include <sge/sprite/detail/pos3.hpp>
#include <sge/sprite/detail/pos2.hpp>
#include <sge/sprite/detail/tex_pos.hpp>
#include <sge/sprite/detail/constants.hpp>
#include <sge/renderer/vf/vertex.hpp>
#include <sge/image/color/any/convert.hpp>
#include <sge/math/matrix/basic_impl.hpp>
#include <sge/math/matrix/vector.hpp>
#include <sge/math/matrix/static.hpp>
#include <sge/math/vector/arithmetic.hpp>
#include <sge/math/vector/construct.hpp>
#include <sge/math/vector/structure_cast.hpp>
#include <sge/math/box/basic_impl.hpp>
#include <sge/math/box/structure_cast.hpp>
#include <sge/variant/object_impl.hpp>
#include <tr1/array>
#include <boost/foreach.hpp>
#include <cmath>

namespace
{

typedef sge::math::box::rect<
	sge::sprite::funit
>::type frect;

}

sge::sprite::detail::vertex_iterator const
sge::sprite::detail::fill_tex_coordinates(
	vertex_iterator it,
	tex_rect const &rt)
{
	(*it++).set<vertex_texpos>(tex_pos(rt.left(), rt.top()));
	(*it++).set<vertex_texpos>(tex_pos(rt.right(), rt.top()));
	(*it++).set<vertex_texpos>(tex_pos(rt.right(), rt.bottom()));
	(*it++).set<vertex_texpos>(tex_pos(rt.left(), rt.bottom()));

	return it;
}

sge::sprite::detail::vertex_iterator const
sge::sprite::detail::fill_vertices(
	vertex_iterator const it,
	rect const &rs,
	tex_rect const &rt,
	depth_type const z)
{
	fill_position(it, rs, z);
	return fill_tex_coordinates(it, rt);
}

sge::sprite::detail::vertex_iterator const
sge::sprite::detail::fill_color(
	vertex_iterator it,
	color const acol)
{
	base_color const col(
		image::color::any::convert<
			base_color::format
		>(
			acol
		)
	);

	for(unsigned i = 0; i < detail::vertices_per_sprite; ++i)
		(*it++).set<vertex_color>(col);
	return it;
}
