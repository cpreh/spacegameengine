//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_PROJECTILE_TRIANGULATION_DETAIL_SNIP_HPP_INCLUDED
#define SGE_PROJECTILE_TRIANGULATION_DETAIL_SNIP_HPP_INCLUDED

#include <sge/projectile/triangulation/detail/point_inside_triangle.hpp>
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
	typename PointContainer,
	typename IndexContainer
>
bool
snip(
	PointContainer const &_contour,
	typename PointContainer::size_type const _prev_vertex,
	typename PointContainer::size_type const _cur_vertex,
	typename PointContainer::size_type const _next_vertex,
	typename PointContainer::size_type const _num_vertices,
	IndexContainer const &_indices,
	typename sge::projectile::triangulation::traits::scalar<
		typename PointContainer::value_type,
		Tag
	>::type const _epsilon
)
{
	typedef typename
	PointContainer::size_type
	size_type;

	typedef typename
	PointContainer::value_type
	vertex;

	typedef sge::projectile::triangulation::traits::access_element<
		vertex,
		Tag
	> access_element;

	typedef typename
	sge::projectile::triangulation::traits::scalar<
		vertex,
		Tag
	>::type
	scalar;

	vertex const
		v1(
			_contour[
				_indices[
					_prev_vertex
				]
			]
		),
		v2(
			_contour[
				_indices[
					_cur_vertex
				]
			]
		),
		v3(
			_contour[
				_indices[
					_next_vertex
				]
			]
		);

	scalar const
		v10(
			access_element::execute(
				v1,
				0
			)
		),
		v11(
			access_element::execute(
				v1,
				1
			)
		),
		v20(
			access_element::execute(
				v2,
				0
			)
		),
		v21(
			access_element::execute(
				v2,
				1
			)
		),
		v30(
			access_element::execute(
				v3,
				0
			)
		),
		v31(
			access_element::execute(
				v3,
				1
			)
		);

	if(
		_epsilon >
		(
			(
				(v20 - v10)
				*
				(v31 - v11)
			)
			-
			(
				(v21 - v11)
				*
				(v30 - v10)
			)
		)
	)
		return false;

	for(
		size_type index(
			0u
		);
		index < _num_vertices;
		++index
	)
	{
		if(
			(index == _prev_vertex)
			|| (index == _cur_vertex)
			|| (index == _next_vertex)
		)
			continue;

		if(
			sge::projectile::triangulation::detail::point_inside_triangle<
				Tag
			>(
				v1,
				v2,
				v3,
				_contour[
					_indices[
						index
					]
				]
			)
		)
			return false;
	}

	return true;
}

}
}
}
}

#endif
