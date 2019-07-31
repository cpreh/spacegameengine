//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


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
	typedef sge::projectile::triangulation::traits::access_element<
		Vertex,
		Tag
	> access_element;

	typedef typename
	sge::projectile::triangulation::traits::scalar<
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
