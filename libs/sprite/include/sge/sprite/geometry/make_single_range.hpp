//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_SPRITE_GEOMETRY_MAKE_SINGLE_RANGE_HPP_INCLUDED
#define SGE_SPRITE_GEOMETRY_MAKE_SINGLE_RANGE_HPP_INCLUDED

#include <sge/sprite/object_fwd.hpp>
#include <sge/sprite/geometry/random_access_range_impl.hpp>


namespace sge
{
namespace sprite
{
namespace geometry
{

template<
	typename Choices
>
sge::sprite::geometry::random_access_range<
	sge::sprite::object<
		Choices
	> *
>
make_single_range(
	sge::sprite::object<
		Choices
	> &_object
)
{
	return
		sge::sprite::geometry::random_access_range<
			sge::sprite::object<
				Choices
			> *
		>(
			&_object,
			&_object + 1 // NOLINT(cppcoreguidelines-pro-bounds-pointer-arithmetic)
		);
}

template<
	typename Choices
>
sge::sprite::geometry::random_access_range<
	sge::sprite::object<
		Choices
	> const *
>
make_single_range(
	sge::sprite::object<
		Choices
	> const &_object
)
{
	return
		sge::sprite::geometry::random_access_range<
			sge::sprite::object<
				Choices
			> const *
		>(
			&_object,
			&_object + 1 // NOLINT(cppcoreguidelines-pro-bounds-pointer-arithmetic)
		);
}

}
}
}

#endif
