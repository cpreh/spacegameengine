//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_SPRITE_GEOMETRY_MAKE_RANDOM_ACCESS_RANGE_HPP_INCLUDED
#define SGE_SPRITE_GEOMETRY_MAKE_RANDOM_ACCESS_RANGE_HPP_INCLUDED

#include <sge/sprite/geometry/random_access_range_impl.hpp>


namespace sge
{
namespace sprite
{
namespace geometry
{

template<
	typename Iterator
>
sge::sprite::geometry::random_access_range<
	Iterator
>
make_random_access_range(
	Iterator const _begin,
	Iterator const _end
)
{
	return
		sge::sprite::geometry::random_access_range<
			Iterator
		>(
			_begin,
			_end
		);
}

template<
	typename Container
>
sge::sprite::geometry::random_access_range<
	typename Container::iterator
>
make_random_access_range(
	Container &_container
)
{
	return
		sge::sprite::geometry::make_random_access_range(
			_container.begin(),
			_container.end()
		);
}

template<
	typename Container
>
sge::sprite::geometry::random_access_range<
	typename Container::const_iterator
>
make_random_access_range(
	Container const &_container
)
{
	return
		sge::sprite::geometry::make_random_access_range(
			_container.begin(),
			_container.end()
		);
}

}
}
}

#endif
