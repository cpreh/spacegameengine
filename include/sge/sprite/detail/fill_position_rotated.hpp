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


#ifndef SGE_SPRITE_DETAIL_FILL_POSITION_ROTATED_HPP_INCLUDED
#define SGE_SPRITE_DETAIL_FILL_POSITION_ROTATED_HPP_INCLUDED

#include <sge/sprite/detail/point_float.hpp>
#include <sge/sprite/detail/rect_float.hpp>
#include <sge/sprite/detail/vertices_per_sprite.hpp>
#include <sge/sprite/object_impl.hpp>
#include <sge/sprite/bounding_rect.hpp>
#include <sge/sprite/depth_type.hpp>
#include <sge/math/matrix/static.hpp>
#include <sge/math/matrix/basic_impl.hpp>
#include <sge/math/box/structure_cast.hpp>
#include <sge/math/vector/structure_cast.hpp>
#include <sge/math/vector/construct.hpp>
#include <boost/foreach.hpp>
#include <tr1/array>
#include <cmath>

namespace sge
{
namespace sprite
{
namespace detail
{

template<
	typename Iterator,
	typename Choices,
	typename Elements
>
void
fill_position_rotated(
	Iterator iterator,
	object<
		Choices,
		Elements
	> const &spr
)
{
	typedef typename Choices::float_type funit;

	typedef typename point_float<
		Choices
	>::type pos2;

	pos2 const centerf(
		math::vector::structure_cast<
			pos2
		>(
			spr.rotation_center()
		)
	);

	typedef typename detail::rect_float<
		Choices
	>::type float_rect;

	float_rect const rbs(
		math::box::structure_cast<
			float_rect
		>(
			sprite::bounding_rect(
				spr
			)
		)
	);

	typedef std::tr1::array<
		pos2,
		detail::vertices_per_sprite
	> position_array;

	position_array const positions = {{
		pos2(
			rbs.left(),
			rbs.top()
		) - centerf,
		pos2(
			rbs.right(),
			rbs.top()
		) - centerf,
		pos2(
			rbs.right(),
			rbs.bottom()
		) - centerf,
		pos2(
			rbs.left(),
			rbs.bottom()
		) - centerf
	}};

	typedef typename sprite::rotation_type<
		Choices
	>::type rotation_type;
	
	rotation_type const rot(
		spr.rotation()
	);

	funit const
		sinx = std::sin(rot),
		cosx = std::cos(rot);

	typedef typename math::matrix::static_<
		funit,
		2,
		2
	>::type matrix2x2;
	
	matrix2x2 const mat_rot(
		cosx, -sinx,
		sinx,  cosx
	);

	typedef typename detail::vertex_pos<
		Choices,
		Elements
	>::type vertex_pos;

	typedef typename sprite::depth_type<
		Choices
	>::type depth_type;

	depth_type const depth_(
		spr.z()
	);

	/*BOOST_FOREACH(
		position_array::const_reference pos_,
		positions
	)*/
	for(
		typename position_array::const_iterator it(
			positions.begin()
		);
		it != positions.end();
		++it
	)
		(*iterator++). template set<
			vertex_pos
		>(
			construct(
				(mat_rot * *it) + centerf,
				depth_
			)
		);
}

}
}
}

#endif
