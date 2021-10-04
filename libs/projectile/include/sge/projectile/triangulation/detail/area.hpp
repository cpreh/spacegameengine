//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_PROJECTILE_TRIANGULATION_DETAIL_AREA_HPP_INCLUDED
#define SGE_PROJECTILE_TRIANGULATION_DETAIL_AREA_HPP_INCLUDED

#include <sge/projectile/triangulation/traits/access_element.hpp>
#include <sge/projectile/triangulation/traits/scalar.hpp>


namespace sge::projectile::triangulation::detail
{

template<
	typename Tag,
	typename PointContainer
>
typename sge::projectile::triangulation::traits::scalar<
	typename PointContainer::value_type,
	Tag
>::type
area(
	PointContainer const &_contour
)
{
	using
	size_type
	=
	typename
	PointContainer::size_type;

	using
	vertex
	=
	typename
	PointContainer::value_type;

	using
	access_element
	=
	sge::projectile::triangulation::traits::access_element<
		vertex,
		Tag
	>;

	using
	scalar
	=
	typename
	sge::projectile::triangulation::traits::scalar<
		vertex,
		Tag
	>::type;

	auto result(
		static_cast<
			scalar
		>(
			0
		)
	);

	for(
		auto
			p1(
				static_cast<
					size_type
				>(
					_contour.size() - 1U
				)
			),
			p2(
				static_cast<
					size_type
				>(
					0
				)
			);
			p2 < _contour.size();
			p1 = p2++
	)
	{
		result =
			static_cast<
				scalar
			>(
				result
				+
				access_element::execute(
					_contour[
						p1
					],
					0
				)
				*
				access_element::execute(
					_contour[
						p2
					],
					1
				)
				-
				access_element::execute(
					_contour[
						p2
					],
					0
				)
				*
				access_element::execute(
					_contour[
						p1
					],
					1
				)
			);
	}

	return
		static_cast<
			scalar
		>(
			result
			/
			static_cast<
				scalar
			>(
				2
			)
		);
}

}

#endif
