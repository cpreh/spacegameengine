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


#ifndef SGE_SPRITE_DETAIL_FILL_POSITON_ROTATED_HPP_INCLUDED
#define SGE_SPRITE_DETAIL_FILL_POSITON_ROTATED_HPP_INCLUDED

#include <sge/sprite/float_point.hpp>

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
	typedef typename float_point<
		Choices
	>::type pos;

	pos2 const centerf(
		math::vector::structure_cast<
			pos2
		>(
			spr.rotation_center()
		)
	);

	typedef std::tr1::array<
		pos2,
		detail::vertices_per_sprite
	> position_array;

	position_array const positions = {{
		pos2(
			static_cast<funit>(rbs.left()),
			static_cast<funit>(rbs.top())
		) - centerf,
		pos2(
			static_cast<funit>(rbs.right()),
			static_cast<funit>(rbs.top())
		) - centerf,
		pos2(
			static_cast<funit>(rbs.right()),
			static_cast<funit>(rbs.bottom())
		) - centerf,
		pos2(
			static_cast<funit>(rbs.left()),
			static_cast<funit>(rbs.bottom())
		) - centerf
	}};

	funit const
		sinx = std::sin(rot),
		cosx = std::cos(rot);

	math::matrix::static_<
		funit,
		2,
		2
	>::type const mat_rot(
		cosx, -sinx,
		sinx,  cosx
	);

	typedef typename detail::vertex_pos<
		Choices,
		Elements
	>::type vertex_pos;

	BOOST_FOREACH(
		position_array::const_reference p,
		positions
	)
		(*iterator++).set<
			vertex_pos
		>(
			construct(
				(mat_rot * p) + centerf,
				z
			)
		);
}

}
}
}

#endif
