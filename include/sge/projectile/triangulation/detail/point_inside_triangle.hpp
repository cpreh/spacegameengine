/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2011 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#ifndef SGE_PROJECTILE_TRIANGULATION_DETAIL_POINT_INSIDE_TRIANGLE_HPP_INCLUDED
#define SGE_PROJECTILE_TRIANGULATION_DETAIL_POINT_INSIDE_TRIANGLE_HPP_INCLUDED

#include <sge/projectile/triangulation/traits/access_element.hpp>
#include <sge/projectile/triangulation/traits/scalar.hpp>

namespace sge
{
namespace projectile
{
namespace triangulation
{
namespace detail
{

template<
	typename Tag,
	typename Vertex
>
bool
point_inside_triangle(
	Vertex const &_v1,
	Vertex const &_v2,
	Vertex const &_v3,
	Vertex const &_point
)
{
	typedef traits::access_element<
		Vertex,
		Tag
	> access_element;

	typedef typename
	traits::scalar<
		Vertex,
		Tag
	>::type
	scalar;

	scalar const
		v10(
			access_element::execute(
				_v1,
				0
			)
		),
		v11(
			access_element::execute(
				_v1,
				1
			)
		),
		v20(
			access_element::execute(
				_v2,
				0
			)
		),
		v21(
			access_element::execute(
				_v2,
				1
			)
		),
		v30(
			access_element::execute(
				_v3,
				0
			)
		),
		v31(
			access_element::execute(
				_v3,
				1
			)
		),
		p0(
			access_element::execute(
				_point,
				0
			)
		),
		p1(
			access_element::execute(
				_point,
				1
			)
		),
		ax(
			v30 - v20
		),
		ay(
			v31 - v21
		),
		bx(
			v10 - v30
		),
		by(
			v11 - v31
		),
		cx(
			v20 - v10
		),
		cy(
			v21 - v11
		),
		apx(
			p0 - v10
		),
		apy(
			p1 - v11
		),
		bpx(
			p0 - v20
		),
		bpy(
			p1 - v21
		),
		cpx(
			p0 - v30
		),
		cpy(
			p1 - v31
		),
		a_cross_bp(
			ax * bpy - ay * bpx
		),
		c_cross_ap(
			cx * apy - cy * apx
		),
		b_cross_cp(
			bx * cpy - by * cpx
		),
		zero(
			static_cast<
				scalar
			>(
				0
			)
		);

	return
		a_cross_bp >= zero
		&&
		b_cross_cp >= zero
		&&
		c_cross_ap >= zero;
}

}
}
}
}

#endif
