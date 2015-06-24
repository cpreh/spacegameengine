/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2015 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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
