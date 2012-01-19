/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2012 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#ifndef SGE_SPRITE_GEOMETRY_SORT_AND_UPDATE_HPP_INCLUDED
#define SGE_SPRITE_GEOMETRY_SORT_AND_UPDATE_HPP_INCLUDED

#include <sge/sprite/geometry/sort.hpp>
#include <sge/sprite/geometry/update.hpp>


namespace sge
{
namespace sprite
{
namespace geometry
{

template<
	typename Range,
	typename Buffers,
	typename Compare
>
void
sort_and_update(
	Range const &_range,
	Buffers &_buffers,
	Compare const &_compare
)
{
	sge::sprite::geometry::sort(
		_range,
		_compare
	);

	sge::sprite::geometry::update(
		_range,
		_buffers
	);
}

}
}
}

#endif
