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


#ifndef SGE_SPRITE_DETAIL_GEOMETRY_SORT_HPP_INCLUDED
#define SGE_SPRITE_DETAIL_GEOMETRY_SORT_HPP_INCLUDED

#include <sge/sprite/geometry/is_random_access_range.hpp>
#include <sge/sprite/intrusive/is_range.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/utility/enable_if.hpp>
#include <algorithm>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace sprite
{
namespace detail
{
namespace geometry
{

template<
	typename Range,
	typename Compare
>
typename boost::enable_if<
	sge::sprite::geometry::is_random_access_range<
		Range
	>,
	void
>::type
sort(
	Range const &_range,
	Compare const &_compare
)
{
	std::stable_sort(
		_range.begin(),
		_range.end(),
		_compare
	);
}

template<
	typename Range,
	typename Compare
>
typename boost::enable_if<
	sge::sprite::intrusive::is_range<
		Range
	>,
	void
>::type
sort(
	Range const &_range,
	Compare const &_compare
)
{
	_range.sort(
		_compare
	);
}

}
}
}
}

#endif
