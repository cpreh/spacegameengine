//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_SPRITE_GEOMETRY_SORT_AND_UPDATE_HPP_INCLUDED
#define SGE_SPRITE_GEOMETRY_SORT_AND_UPDATE_HPP_INCLUDED

#include <sge/sprite/geometry/sort.hpp>
#include <sge/sprite/geometry/update.hpp>
#include <sge/sprite/render/range_impl.hpp>


namespace sge::sprite::geometry
{

template<
	typename Range,
	typename Buffers,
	typename Compare
>
inline
sge::sprite::render::range<
	typename Buffers::choices
>
sort_and_update(
	Range const &_range,
	Compare const &_compare,
	Buffers &_buffers
)
{
	sge::sprite::geometry::sort(
		_range,
		_compare
	);

	return
		sge::sprite::geometry::update(
			_range,
			_compare,
			_buffers
		);
}

}

#endif
