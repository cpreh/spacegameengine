//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_PROJECTILE_TRIANGULATION_TRIANGULATE_HPP_INCLUDED
#define SGE_PROJECTILE_TRIANGULATION_TRIANGULATE_HPP_INCLUDED

#include <sge/projectile/triangulation/detail/area.hpp>
#include <sge/projectile/triangulation/detail/snip.hpp>
#include <sge/projectile/triangulation/traits/insert_result.hpp>
#include <sge/projectile/triangulation/traits/scalar.hpp>
#include <fcppt/assert/pre.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/range/algorithm_ext/iota.hpp>
#include <vector>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace projectile
{
namespace triangulation
{

template<
	typename Tag,
	typename ResultContainer,
	typename ContourContainer
>
ResultContainer
triangulate(
	ContourContainer const &_contour,
	typename sge::projectile::triangulation::traits::scalar<
		typename ContourContainer::value_type,
		Tag
	>::type const _epsilon
)
{
	typedef typename
	ContourContainer::size_type
	size_type;

	typedef typename
	ContourContainer::value_type
	vertex;

	typedef typename
	sge::projectile::triangulation::traits::scalar<
		vertex,
		Tag
	>::type
	scalar;

	FCPPT_ASSERT_PRE(
		_contour.size()
		>=
		static_cast<
			size_type
		>(
			3
		)
	);

	typedef
	std::vector<
		size_type
	>
	index_vector;

	index_vector indices(
		_contour.size()
	);

	// TODO: Initialize this directly
	// we want a counter-clockwise polygon in indices
	if(
		static_cast<
			scalar
		>(
			0
		)
		<
		sge::projectile::triangulation::detail::area<
			Tag
		>(
			_contour
		)
	)
		boost::iota(
			indices,
			static_cast<
				size_type
			>(
				0
			)
		);
	else
		for(
			size_type index = 0;
			index < indices.size();
			++index
		)
			indices[
				index
			]
			=
			static_cast<
				size_type
			>(
				(
					_contour.size()
					-1u
				)
			)
			- index;

	size_type num_vertices(
		_contour.size()
	);

	ResultContainer result;

	for(
		size_type cur_vertex(
			static_cast<
				size_type
			>(
				num_vertices - 1u
			)
		)
		;
		num_vertices > 2u
		;
		--num_vertices
	)
	{
		// three consecutive vertices in current polygon
		size_type prev_vertex(
			cur_vertex
		);

		if(
			num_vertices <= prev_vertex
		)
			prev_vertex = 0;

		cur_vertex = prev_vertex + 1u;

		if(
			num_vertices <= cur_vertex
		)
			cur_vertex = 0;

		size_type next_vertex(
			cur_vertex + 1u
		);

		if(
			num_vertices <= next_vertex
		)
			next_vertex = 0;

		if(
			sge::projectile::triangulation::detail::snip<
				Tag
			>(
				_contour,
				prev_vertex,
				cur_vertex,
				next_vertex,
				num_vertices,
				indices,
				_epsilon
			)
		)
		{
			sge::projectile::triangulation::traits::insert_result<
				ResultContainer,
				vertex,
				Tag
			>::execute(
				result,
				_contour[
					indices[
						prev_vertex
					]
				],
				_contour[
					indices[
						cur_vertex
					]
				],
				_contour[
					indices[
						next_vertex
					]
				]
			);

			// remove v from remaining polygon
			for(
				size_type cur(
					cur_vertex +1u
				);
				cur < num_vertices;
				++cur
			)
				indices[
					cur - 1u
				] =
					indices[
						cur
					];
		}
	}

	return result;
}

}
}
}

#endif
