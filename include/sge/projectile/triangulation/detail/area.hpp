/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2016 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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
