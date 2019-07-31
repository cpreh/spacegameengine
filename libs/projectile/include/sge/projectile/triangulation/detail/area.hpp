//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_PROJECTILE_TRIANGULATION_DETAIL_AREA_HPP_INCLUDED
#define SGE_PROJECTILE_TRIANGULATION_DETAIL_AREA_HPP_INCLUDED

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
	typedef typename
	PointContainer::size_type
	size_type;

	typedef typename
	PointContainer::value_type vertex;

	typedef
	sge::projectile::triangulation::traits::access_element<
		vertex,
		Tag
	> access_element;

	typedef typename
	sge::projectile::triangulation::traits::scalar<
		vertex,
		Tag
	>::type
	scalar;

	scalar result(
		static_cast<
			scalar
		>(
			0
		)
	);

	for(
		size_type
			p1(
				static_cast<
					size_type
				>(
					_contour.size() - 1u
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
}
}
}

#endif
