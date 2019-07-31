//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_SPRITE_GEOMETRY_UPDATE_HPP_INCLUDED
#define SGE_SPRITE_GEOMETRY_UPDATE_HPP_INCLUDED

#include <sge/sprite/geometry/fill.hpp>
#include <sge/sprite/render/range_impl.hpp>


namespace sge
{
namespace sprite
{
namespace geometry
{

/**
\brief Fill sprite geometry into a new buffer slice

Fills sprite geometry from the sprites in \a _range into a new slice obtained
from \a _buffers. \a _compare is used to determine which sprites can be
rendered together.

\param _range The sprite range to use

\param _compare The compare function to determine which sprites can be rendered
together

\param _buffers The buffers to obtain a new slice from

\return A render range which describes how the sprites are rendered
*/
template<
	typename Range,
	typename Compare,
	typename Buffers
>
inline
sge::sprite::render::range<
	typename
	Buffers::choices
>
update(
	Range const &_range,
	Compare const &_compare,
	Buffers &_buffers
)
{
	return
		_range.empty()
		?
			sge::sprite::render::range<
				typename
				Buffers::choices
			>()
		:
			sge::sprite::geometry::fill(
				_range,
				_compare,
				_buffers.allocate(
					_range.size()
				)
			)
		;
}

}
}
}

#endif
